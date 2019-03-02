#include"FriendItem.h"
#include"ShareData.h"
#include"GameData.h"
#include"CommonHead.h"
#include"Commen.h"

bool FriendItem::init(const Player_Info & info)
{
	if (Layout::init())
	{
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
		m_btnVec.push_back(addBtn);
		auto agreeBtn = Button::create(StringValue("TeamOkBtn"));
		this->addChild(agreeBtn);
		agreeBtn->setTag(5);
		agreeBtn->setPosition(Vec2(size.width - 60, size.height*0.5));
		m_btnVec.push_back(agreeBtn);
		auto rejectBtn = Button::create(StringValue("TeamRefuseBtn"));
		this->addChild(rejectBtn);
		rejectBtn->setTag(6);
		rejectBtn->setPosition(Vec2(agreeBtn->getPositionX() - 60, size.height*0.5));
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
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	default:
		break;
	}
}

