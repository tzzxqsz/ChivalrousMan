#pragma once
#ifndef __FRIEND_LAYER_H__
#define __FRIEND_LAYER_H__
#include"PreProcess.h"
#include"CommonTouchLayer.h"
#include"CSBaseView.h"

class FriendLayer :public CSBaseView
{
	CLASS_ESSENTAIL(FriendLayer)
public:
	static CommonTouchLayer* create();

	bool init() override;

	void onEnter() override;

	void onExit() override;

	void onAddFriendClick(cocos2d::Ref* sender);
private:
	
};

#endif // !__FRIEND_LAYER_H__

