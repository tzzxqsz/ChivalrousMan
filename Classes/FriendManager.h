#pragma once
#ifndef __FRIEND_MAMAGER_H__
#define __FRIEND_MAMAGER_H__
#include"PreProcess.h"
#include<string>
#include<list>

struct GameFriend
{
	std::string playername;
	std::string rolename;
};

/*
*class FriendManager
*玩家好友管理
*/
class FriendManager
{
	CLASS_ESSENTAIL(FriendManager);
	GET_SINGLE_OBJECT(FriendManager);
public:
	/*
	*
	*/
	std::list<GameFriend>& getFriendList() { return m_friendlist; }

	/*
	*addFriend(GameFriend fr);
	*添加朋友
	*@param fr:朋友信息
	*/
	void addFriend(GameFriend fr);
private:
	std::list<GameFriend> m_friendlist;

	SINGLE_ATTRIBUTES(FriendManager);
};

#endif // !__FRIEND_MAMAGER_H__

