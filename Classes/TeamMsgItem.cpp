#include"TeamMsgItem.h"
#include"Commen.h"
#include"GameData.h"
#include"GameDynamicData.h"
#include"SocketManager.h"
#include"TeamLayer.h"
#include"TeamManager.h"
#include"CameraPlayer.h"
#include"ObjectLayer.h"
#include"TipLayer.h"
#include"GameScene.h"
#include"Player.h"
#include"PlayerManager.h"
#include<functional>
#include<list>

TeamMsgItem* TeamMsgItem::create(const int& fd)
{
	auto pRet = new TeamMsgItem;
	if (pRet&&pRet->init(fd))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool TeamMsgItem::init(const int& fd)
{
	if (Node::init())
	{
		m_fd = fd;
		Player_Info info = PlayerManager::getInstance()->findPlayerInfoByFd(m_fd);
		ITEM_COMMEN(TeamMsgItem, StringValue("MsgItemBg"), -110);

		auto OkBtn = MenuItemImage::create(StringValue("TeamOkBtn"), StringValue("TeamOkBtn"), 
			this, menu_selector(TeamMsgItem::onOkBtnClick));
		OkBtn->setPosition(115, 15);
		menu->addChild(OkBtn);
		
		auto RefuseBtn = MenuItemImage::create(StringValue("TeamRefuseBtn"), StringValue("TeamRefuseBtn"),
			this, menu_selector(TeamMsgItem::onRefuseBtnClick));
		RefuseBtn->setPosition(115, -15);
		menu->addChild(RefuseBtn);
		
		return true;
	}
	return false;
}

void TeamMsgItem::onHeadClick(cocos2d::CCObject* sender)
{
	ClickAction(sender);
}

void TeamMsgItem::onOkBtnClick(cocos2d::CCObject* sender)
{
	ClickAction(sender);
	auto info = PlayerManager::getInstance()->findPlayerInfoByFd(m_fd);
	if (info.curmap == GetIntData("CurMap"))
	{
		std::function<void(float)> func = [this](float) {
			((TeamLayer*)this->getParent())->removeMsgItem(this);
			TeamManager::getInstance()->c2sAgreeTeam(this->m_fd);
			auto info = PlayerManager::getInstance()->findPlayerInfoByFd(this->m_fd);
			auto it = CurGameScene()->getObjectLayer()->existPlayer(info.playername, info.rolename);
			CameraPlayer::getPlayerInstance()->moveTo((*it)->getWorldPos(), 1);
		};
		scheduleOnce(func, 0.2, "func12");
	}
	else
	{
		auto tiplayer = TipLayer::createTipLayer(StringValue("NotEqualMap"));
		CurGameScene()->addChild(tiplayer);
	}
}

void TeamMsgItem::onRefuseBtnClick(cocos2d::CCObject* sender)
{
	ClickAction(sender);
	std::function<void(float)> func = [this](float) {
		((TeamLayer*)this->getParent())->removeMsgItem(this);
		TeamManager::getInstance()->c2sRefuseTeam(this->m_fd);
	};
	scheduleOnce(func, 0.2, "func");
}