#include"PlayerItem.h"
#include"tool/Commen.h"
#include"tool/GameData.h"
#include"net/ShareData.h"
#include"tool/GameDynamicData.h"
#include"GameScene.h"
#include"talk/PrivateTalkLayer.h"
#include"CameraPlayer.h"
#include"net/SocketManager.h"
#include"team/TeamManager.h"

PlayerItem* PlayerItem::create(const Player_Info& info)
{
	PlayerItem* pRet = new PlayerItem;
	if (pRet&&pRet->init(info))
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

bool PlayerItem::init(const Player_Info& info)
{
	if (Node::init())
	{
		ITEM_COMMEN(PlayerItem, StringValue("PlayerItemBg"), -80);
		
		auto ptalkBtn = MenuItemImage::create(StringValue("PrivateTalkBtn"),
			StringValue("PrivateTalkBtn"), this, menu_selector(PlayerItem::onPrivateTalkClick));
		ptalkBtn->setPosition(80, 15);
		menu->addChild(ptalkBtn);
		
		auto maketeamBtn = MenuItemImage::create(StringValue("MakeTeamBtn"),
			StringValue("MakeTeamBtn"), this, menu_selector(PlayerItem::onMakeTeamClick));
		maketeamBtn->setPosition(80, -15);
		menu->addChild(maketeamBtn);
		m_fd = info.fd;
		return true;
	}
	return false;
}

void PlayerItem::onHeadClick(cocos2d::CCObject* sender)
{
	ClickAction(sender);
}

void PlayerItem::onPrivateTalkClick(cocos2d::CCObject* sender)
{
	ClickAction(sender);
	auto ptlayer = PrivateTalkLayer::create(m_fd);
	CurGameScene()->addChild(ptlayer);
	getParent()->setVisible(false);
}

void PlayerItem::onMakeTeamClick(cocos2d::CCObject* sender)
{
	ClickAction(sender);
	if (PlayerTeamStatus() == P_STATUS_NORMAL)
	{
		TeamManager::getInstance()->c2sTeamApply(m_fd);
	}
	else
	{
		SetIntData("IsHaveTip", 1);
		SetStringData("TipText", StringValue("MakeTeamFailed"));
	}
}