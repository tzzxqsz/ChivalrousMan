#pragma once
#ifndef __FRIEND_MAMAGER_H__
#define __FRIEND_MAMAGER_H__
#include"PreProcess.h"
#include<string>
#include<list>

//好友信息
struct GameFriend
{
	std::string playername;
	std::string rolename;
	
	bool operator==(const GameFriend& fr)
	{
		this->playername == fr.playername&&this->rolename == fr.rolename;
	}
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
	* getFriendList()
	*获取好友信息列表
	*/
	std::list<GameFriend>& getFriendList() { return m_friendlist; }

	/*
	*addFriend(GameFriend fr);
	*添加朋友
	*@param fr:朋友信息
	*@return int:返回-1表示添加失败，返回0表示添加成功
	*/
	int addFriend(const GameFriend& fr);

	/*
	*delFrinend(const GameFriend& fr)
	*删除好友
	*@param fr:好友信息
	*@return int：返回-1表示删除失败，返回0表示删除成功
	*/
	int delFrinend(const GameFriend& fr);
private:
	std::list<GameFriend> m_friendlist;

	SINGLE_ATTRIBUTES(FriendManager);
};

#endif // !__FRIEND_MAMAGER_H__

