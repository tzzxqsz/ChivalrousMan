#pragma once
#ifndef __TEAM_MANAGER_H__
#define __TEAM_MANAGER_H__
#include"tool/PreProcess.h"
#include"jsonCpp/value.h"
#include"net/ShareData.h"
#include<map>

/*
*class TeamManager
*队伍管理器,暂时队伍人数上限为2个
*/
class TeamManager:public cocos2d::CCObject
{
public:
	GET_SINGLE_OBJECT(TeamManager);

	static void release();

	void c2sTeamApply(const int& dest);

	void c2sRefuseTeam(const int& dest);

	void c2sAgreeTeam(const int& dest);

	void c2sTeamMove(cocos2d::Vec2 target, int dest);

	void c2sTeamGotoMap(std::string map, cocos2d::Vec2 target, int dest);

	void c2sTeamDissolve(const int& dest);

	void c2sTeamFight(int dest, std::string name, int nums);

	void s2cTeamApply(Json::Value&);

	void s2cRefuseTeam(Json::Value&);

	void s2cAgreeTeam(Json::Value&);

	void s2cTeamMove(Json::Value&);

	void s2cTeamGotoMap(Json::Value&);

	void s2cTeamDissolve(Json::Value&);

	void s2cTeamFight(Json::Value&);

	/*
	*创建一个队伍
	*@param fd：玩家唯一标识
	*@param status：成员状态
	*/
	void createTeam(const int& fd, int status);

	/*
	*删除队伍成员
	*@param fd：玩家唯一标识
	*/
	void removeTeamMembers(int fd);

	/*
	*解散队伍
	*/
	void dissolveTeam();

	void applyTeamByRoleName(const std::string& rolename);

	std::map<int, int>& getTeamMembers() { return m_teamMembers; }

	std::list<int>& getApplyTeamList() { return m_applyTeamList; }

	std::list<TeamGotoMap>& getGotoMapMsgs() { return m_gotoMapMsgs; }
private:
	TeamManager();
	~TeamManager();

	std::list<int> m_applyTeamList;          //队伍申请列表
	std::map<int, int> m_teamMembers;   //保存队员
	std::list<TeamGotoMap> m_gotoMapMsgs;            //保存前往某地图消息

	SINGLE_ATTRIBUTES(TeamManager);
};

#endif // !__TEAM_MANAGER_H__

