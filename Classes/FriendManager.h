#pragma once
#ifndef __FRIEND_MANAGER_H__
#define __FRIEND_MANAGER_H__
#include"PreProcess.h"
#include<vector>
#include<list>
#include"ShareData.h"
#include"jsonCpp/value.h"
#include<algorithm>
#include<chrono>

class RandomGenerator
{
public:
	ptrdiff_t operator() (ptrdiff_t max)
	{
		double temp;
		srand(std::chrono::system_clock::now().time_since_epoch().count());
		temp = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
		return static_cast<ptrdiff_t>(temp * max);
	}
};

class FriendManager :public cocos2d::CCObject
{
	GET_SINGLE_OBJECT(FriendManager)
public:
	static const int MAX_ADD_LIST = 15;  //最大添加好友列表
	static const int MAX_FRIEND_LIST = 30;  //最大好友列表
	static const int MAX_APPLY_LIST = 20;  //最大申请列表

	void c2sApplyFriend(const std::string& rolename);

	void c2sAgreeFriend(const Player_Info& info);

	void c2sRejectFriend(const std::string& rolename);

	void c2sDelFriend(const Player_Info& info);

	void s2cApplyFriend(Json::Value& msg);

	void s2cAgreeFriend(Json::Value& msg);

	void s2cRejectFriend(Json::Value& msg);

	void s2cDelFriend(Json::Value& msg);

	std::vector<Player_Info>& getFriendList(const bool& refresh = false);

	std::vector<Player_Info> getAddFriendList();

	std::vector<Player_Info> getApplyFriendList();

	void removeApplyFriendList(const std::string& rolename);

	bool isFriend(const Player_Info& info);

	bool isExitsApply(const Player_Info& info);
private:
	FriendManager();
	~FriendManager();

	std::vector<Player_Info> m_friendList;
	std::vector<Player_Info> m_applyList;

	SINGLE_ATTRIBUTES(FriendManager);
};

#endif //__FRIEND_MANAGER_H__