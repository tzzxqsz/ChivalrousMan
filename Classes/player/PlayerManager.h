#pragma once
#ifndef __PLAYER_MANAGER_H__
#define __PLAYER_MANAGER_H__
#include"tool/PreProcess.h"
#include"net/ShareData.h"
#include"jsonCpp/value.h"

class PlayerManager :cocos2d::CCObject
{
	GET_SINGLE_OBJECT(PlayerManager)
public:
	void c2sInitPlayerData();

	void c2sInitPos();

	void c2sMoveTo(const cocos2d::Vec2& pos, int less = 0);

	void c2sPlayerLeave();

	void c2sVerifyPlayerPos();

	void c2sUpdatePlayerData();

	void s2cInitPlayerData(Json::Value& message);

	void s2cInitPos(Json::Value& message);

	void s2cPlayerLeave(Json::Value& message);

	void s2cMoveTo(Json::Value& message);

	void s2cVerifyPlayerPos(Json::Value& message);

	void s2cUpdatePlayerData(Json::Value& message);

	void PlayerManager::removePlayer(int fd);

	std::string findRoleNameByFd(const int& fd);

	Player_Info findPlayerInfoByFd(const int& fd);

	Player_Info findPlayerInfoByRoleName(const std::string& rolename);

	const std::list<Player_Info>& getPlayerList() { return m_playerlist; }

	std::list<Player_Info>& getAddList() { return m_addList; }
private:
	PlayerManager();
	~PlayerManager();

	std::list<Player_Info> m_playerlist;            //其他玩家列表
	std::list<Player_Info> m_addList;
		
	SINGLE_ATTRIBUTES(PlayerManager);
};

#endif // !__PLAYER_MANAGER_H_

