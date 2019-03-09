#include"TalismanLayer.h"
#include"CommonButton.h"
#include"Commen.h"
#include"Path.h"

bool TalismanLayer::init()
{
	if (CommonTouchLayer::init())
	{
		auto screenSize = SCREEN;
		auto centerPos = Vec2(screenSize.width*0.5, screenSize.height*0.5);
		auto bg = Sprite::create(getBackgroundPath("StyleBg4"));
		bg->setPosition(centerPos);
		auto visibleSize = bg->getContentSize();
		setExcludeRect(bg->getPosition(), bg->getTextureRect());
		this->addChild(bg);
		
		auto leftArrow = CommonButton::createCommonButton(getButtonPath("left_btn"));
		this->addChild(leftArrow);
		leftArrow->setPosition(centerPos.x - visibleSize.width*0.5, centerPos.y);

		auto rightArrow = CommonButton::createCommonButton(getButtonPath("right_btn"));
		this->addChild(rightArrow);
		rightArrow->setPosition(centerPos.x + visibleSize.width*0.5, centerPos.y);

		return true;
	}
	return false;
}

void TalismanLayer::onEnter()
{
	CommonTouchLayer::onEnter();
	
}
