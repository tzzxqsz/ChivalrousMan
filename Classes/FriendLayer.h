#pragma once
#ifndef __FRIEND_LAYER_H__
#include"PreProcess.h"

/*
*class FriendLayer
*���Ѳ㣬������ʾ��ҵĺ���
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

