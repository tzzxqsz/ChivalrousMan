#pragma once
#ifndef __FRIEND_MANAGER_H__
#define __FRIEND_MANAGER_H__
#include"PreProcess.h"

class FriendManager :public cocos2d::CCObject
{
	GET_SINGLE_OBJECT(FriendManager)
public:

private:
	FriendManager();
	
	SINGLE_ATTRIBUTES(FriendManager);
};

#endif // !__FRIEND_MANAGER_H__

