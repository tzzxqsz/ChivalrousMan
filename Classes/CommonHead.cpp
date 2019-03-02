#include "CommonHead.h"
#include"ShareData.h"
#include"GameData.h"
#include"ui/UIButton.h"
#include"Commen.h"

CommonHead::CommonHead()
{
}

CommonHead::~CommonHead()
{
}

bool CommonHead::init(const Player_Info & info)
{
	if (Node::init())
	{
		auto headFrame = Sprite::create(StringValue("HeadFrame"));
		headFrame->setScale(0.8, 0.8);
		this->addChild(headFrame);
		auto head = Button::create(StringValue(info.playertype + "Head"));
		head->addClickEventListener(CC_CALLBACK_1(CommonHead::onHeadClick, this));
		head->setPosition(Vec2(headFrame->getPosition().x - 5, headFrame->getPosition().y + 5));
		this->addChild(head);
		auto namelabel = LabelTTF::create(info.rolename, "¿¬Ìå", 16);
		namelabel->setAnchorPoint(ccp(0, 0.5));
		namelabel->setPosition(head->getPositionX() + 34, 18);
		this->addChild(namelabel);
		auto gradelabel = LabelTTF::create(StringValue("GradeText") + NTS(info.grade), "¿¬Ìå", 16);
		gradelabel->setAnchorPoint(ccp(0, 0.5));
		gradelabel->setColor(Color3B::ORANGE);
		gradelabel->setPosition(head->getPositionX() + 34, -15);
		this->addChild(gradelabel);
		return true;
	}
	return false;
}

void CommonHead::onHeadClick(cocos2d::CCObject * sender)
{
	if (m_callback)
		m_callback(sender);
}

void CommonHead::setCallback(cocos2d::ui::Widget::ccWidgetClickCallback & callback)
{
	m_callback = callback;
}
