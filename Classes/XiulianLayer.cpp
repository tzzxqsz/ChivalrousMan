#include "XiulianLayer.h"
#include"ui/UIImageView.h"
#include"Path.h"
#include"Commen.h"

bool XiulianLayer::init()
{
	if (CommonTouchLayer::init())
	{
		auto size = SCREEN;
		auto bg = cocos2d::Sprite::create(getBackgroundPath("StyleBg8"));
		this->addChild(bg);
		bg->setPosition(Vec2(size.width, size.height));
		setExcludeRect(bg->getPosition(), bg->getTextureRect());

		auto taizi = cocos2d::ui::ImageView::create(getCommonPath("taizi"));
		this->addChild(taizi);
		taizi->setPosition(Vec2(size.width*0.5, size.height*0.5 - 100));
		
		return true;
	}
	return false;
}

void XiulianLayer::onEnter()
{
	CommonTouchLayer::onEnter();

}

void XiulianLayer::onExit()
{
	CommonTouchLayer::onExit();

}
