#include"FriendLayer.h"
#include"Commen.h"
#include"ui/UIButton.h"
#include"LogUtil.h"

CommonTouchLayer* FriendLayer::create()
{
	auto pRet = new FriendLayer;
	if (pRet&&pRet->init())
	{
		auto comm = CommonTouchLayer::createCommonTouchLayer(CommonTouchLayer::BackColor);
		auto pos=pRet->_self["_imageBg"]->getPosition();
		auto size = SCREEN;
		comm->setExcludeRect(pos, cocos2d::Rect(0, 0, size.width, size.height));
		comm->addChild(pRet);
		return comm;
	}
	delete pRet;
	pRet = nullptr;
	return nullptr;
}

bool FriendLayer::init()
{
	Param csb;
	csb["model"] = "friend";
	csb["name"] = "FriendView";
	if (CSBaseView::init(csb))
	{
		dynamic_cast<cocos2d::ui::Button*>(_self["_btnFriend"])->addClickEventListener(CC_CALLBACK_1(FriendLayer::onAddFriendClick, this));
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
	LOG("FriendLayer::onAddFriendClick");
}
