#include"FriendItem.h"
#include"tool/GameData.h"
#include"common/CommonHead.h"
#include"tool/Commen.h"
#include"FriendManager.h"
#include"team/TeamManager.h"
#include"event/SignalManager.h"
#include"event/SignalConst.h"

bool FriendItem::init(const Player_Info & info)
{
	if (Layout::init())
	{
		m_info = info;
		auto bg = Sprite::create(StringValue("MsgItemBg"));
		this->addChild(bg);
		auto size = bg->getContentSize();
		this->setContentSize(Size(size.width, size.height + 10));
		bg->setPosition(size.width*0.5, size.height*0.5 + 5);
		
		auto head = CommonHead::createCommonHead(info);
		this->addChild(head);
		head->setPosition(Vec2(50, size.height*0.5));

		auto talkBtn = Button::create(StringValue("PrivateTalkBtn"));
		this->addChild(talkBtn);
		talkBtn->setTag(1);
		talkBtn->setPosition(Vec2(size.width - 40, size.height*0.5));	
		talkBtn->addClickEventListener(CC_CALLBACK_1(FriendItem::onBtnClick, this));
		m_btnVec.push_back(talkBtn);
		auto teamBtn = Button::create(StringValue("MakeTeamBtn"));
		this->addChild(teamBtn);
		teamBtn->setTag(2);
		teamBtn->setPosition(Vec2(talkBtn->getPositionX() - 60, size.height*0.5));
		teamBtn->addClickEventListener(CC_CALLBACK_1(FriendItem::onBtnClick, this));
		m_btnVec.push_back(teamBtn);
		auto delBtn = Button::create(StringValue("DelFriendBtn"));
		this->addChild(delBtn);
		delBtn->setTag(3);
		delBtn->setPosition(Vec2(teamBtn->getPositionX() - 60, size.height*0.5));
		delBtn->addClickEventListener(CC_CALLBACK_1(FriendItem::onBtnClick, this));
		m_btnVec.push_back(delBtn);
		auto addBtn = Button::create(StringValue("AddFriendBtn"));
		this->addChild(addBtn);
		addBtn->setTag(4);
		addBtn->setPosition(teamBtn->getPosition());
		addBtn->addClickEventListener(CC_CALLBACK_1(FriendItem::onBtnClick, this));
		m_btnVec.push_back(addBtn);
		auto agreeBtn = Button::create(StringValue("TeamOkBtn"));
		this->addChild(agreeBtn);
		agreeBtn->setTag(5);
		agreeBtn->setPosition(Vec2(size.width - 60, size.height*0.5));
		agreeBtn->addClickEventListener(CC_CALLBACK_1(FriendItem::onBtnClick, this));
		m_btnVec.push_back(agreeBtn);
		auto rejectBtn = Button::create(StringValue("TeamRefuseBtn"));
		this->addChild(rejectBtn);
		rejectBtn->setTag(6);
		rejectBtn->setPosition(Vec2(agreeBtn->getPositionX() - 60, size.height*0.5));
		rejectBtn->addClickEventListener(CC_CALLBACK_1(FriendItem::onBtnClick, this));
		m_btnVec.push_back(rejectBtn);
		
		return true;
	}
	return false;
}

void FriendItem::setStatus(const std::initializer_list<bool>& list)
{
	int count = 0;
	int size = m_btnVec.size();
	for (auto flag : list)
	{
		if (count > size - 1)
		{
			return;
		}
		m_btnVec[count]->setVisible(flag);
		++count;
	}
}

void FriendItem::onBtnClick(cocos2d::CCObject* sender)
{
	int tag = dynamic_cast<Button*>(sender)->getTag();
	switch (tag)
	{
	case 1:   // 私聊
		SignalManager::getInstance()->dispatch(EVENT_GOTO_TALK);
		break;
	case 2:   //组队
		TeamManager::getInstance()->applyTeamByRoleName(m_info.rolename);
		break;
	case 3:   //删除
		FriendManager::getInstance()->c2sDelFriend(m_info);
		break;
	case 4:   //添加
		FriendManager::getInstance()->c2sApplyFriend(m_info.rolename);
		break;
	case 5:  //同意
		FriendManager::getInstance()->c2sAgreeFriend(m_info);
		break;
	case 6:   //拒绝
		FriendManager::getInstance()->c2sRejectFriend(m_info.rolename);
		break;
	default:
		break;
	}
}

