#pragma once
#ifndef __FRIEND_LAYER_H__
#define __FRIEND_LAYER_H__
#include"PreProcess.h"
#include"CommonTouchLayer.h"

class FriendLayer :public CommonTouchLayer
{
	CLASS_ESSENTAIL(FriendLayer)
public:
	CREATE_FUNC(FriendLayer)

	bool init() override;

	void onEnter() override;

	void onExit() override;

	void onAddFriendClick(cocos2d::Ref* sender);
private:
	
};

#endif // !__FRIEND_LAYER_H__

