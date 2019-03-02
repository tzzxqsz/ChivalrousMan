#include"FriendLayer.h"
#include"Commen.h"
#include"GameData.h"


bool FriendLayer::init()
{
	if (CommonTouchLayer::init())
	{
		auto size = SCREEN;
		auto bg = Sprite::create(StringValue(""));
		bg->setPosition(size.width*0.5, size.height*0.5);
		this->addChild(bg);
		setExcludeRect(bg->getPosition(), bg->getTextureRect());

		
		return true;
	}
	return false;
}

void FriendLayer::onEnter()
{
}

void FriendLayer::onExit()
{

}

void FriendLayer::onAddFriendClick(cocos2d::Ref * sender)
{

}
