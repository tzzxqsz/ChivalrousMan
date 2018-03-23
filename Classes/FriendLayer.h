#pragma once
#ifndef __FRIEND_LAYER_H__
#include"PreProcess.h"

/*
*class FriendLayer
*好友层，用于显示玩家的好友
*/
class FriendLayer Inherit(cocos2d::Layer)
{
	CLASS_ESSENTAIL(FriendLayer)
	CREATE_FUNC(FriendLayer)
public:
	bool init() override;
private:
};

#endif // !__FRIEND_LAYER_H__

