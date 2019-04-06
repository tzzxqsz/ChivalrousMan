#include"CommonTouchLayer.h"
#include"Commen.h"

cocos2d::Color4B CommonTouchLayer::BackColor = cocos2d::Color4B(0x4d, 0x4d, 0x4d, 155);

CommonTouchLayer::CommonTouchLayer()
{
}

CommonTouchLayer::~CommonTouchLayer()
{
}

bool CommonTouchLayer::init(const cocos2d::Color4B& color)
{
	if (cocos2d::LayerColor::initWithColor(color))
	{
		cocos2d::Size size = cocos2d::Director::sharedDirector()->getWinSize();
		this->setContentSize(size);
		LISTEN_TOUCH(CommonTouchLayer);
		touchListener->setSwallowTouches(true);
		return true;
	}
	return false;
}

void CommonTouchLayer::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	if (!m_touchClose)
		return;
	auto touchPos = touch->getLocation();
	if (!m_excludeRect.containsPoint(touchPos))
		this->removeFromParent();
}

bool CommonTouchLayer::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * unused_event)
{
	return true;
}

void CommonTouchLayer::setTouchClose(const bool& touchClose)
{
	m_touchClose = touchClose;
}

void CommonTouchLayer::setExcludeRect(const cocos2d::Point & center, const cocos2d::Rect & rect)
{
	m_excludeRect = rect;
	m_excludeRect.origin.x = center.x - rect.size.width*0.5;
	m_excludeRect.origin.y = center.y - rect.size.height*0.5;
}

void CommonTouchLayer::onEnter()
{
	LayerColor::onEnter();
}

void  CommonTouchLayer::onClicked()
{

}

