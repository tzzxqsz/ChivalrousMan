#include "MaxTopLayer.h"
#include"event/SignalConst.h"
#include"event/SignalManager.h"
#include"common/TipLayer.h"

void MaxTopLayer::attach()
{
	auto pRet = new MaxTopLayer;
	if (pRet&&pRet->init())
	{
		pRet->autorelease();
		pRet->setZOrder(999);
		cocos2d::Director::getInstance()->setNotificationNode(pRet);
	}
	else
	{
		delete pRet;
		pRet = nullptr;
	}
}

void MaxTopLayer::onEnter()
{
	Node::onEnter();
	auto slot = SignalManager::getInstance()->add(EVENT_TIPS, handler(this, SEL_EVENTFUNC(MaxTopLayer::popupTips)));
	m_slots.push_back(slot);
}

void MaxTopLayer::onExit()
{
	Node::onExit();
	for (auto var : m_slots)
	{
		var->remove();
	}
}

void MaxTopLayer::popupTips(Json::Value & msg)
{
	auto tips = TipLayer::createTipLayer(msg["content"].asString());
	this->addChild(tips);
}