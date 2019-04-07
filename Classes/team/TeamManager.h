#pragma once
#ifndef __TEAM_MANAGER_H__
#define __TEAM_MANAGER_H__
#include"tool/PreProcess.h"
#include"jsonCpp/value.h"
#include"net/ShareData.h"
#include<map>

/*
*class TeamManager
*���������,��ʱ������������Ϊ2��
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
	*����һ������
	*@param fd�����Ψһ��ʶ
	*@param status����Ա״̬
	*/
	void createTeam(const int& fd, int status);

	/*
	*ɾ�������Ա
	*@param fd�����Ψһ��ʶ
	*/
	void removeTeamMembers(int fd);

	/*
	*��ɢ����
	*/
	void dissolveTeam();

	void applyTeamByRoleName(const std::string& rolename);

	std::map<int, int>& getTeamMembers() { return m_teamMembers; }

	std::list<int>& getApplyTeamList() { return m_applyTeamList; }

	std::list<TeamGotoMap>& getGotoMapMsgs() { return m_gotoMapMsgs; }
private:
	TeamManager();
	~TeamManager();

	std::list<int> m_applyTeamList;          //���������б�
	std::map<int, int> m_teamMembers;   //�����Ա
	std::list<TeamGotoMap> m_gotoMapMsgs;            //����ǰ��ĳ��ͼ��Ϣ

	SINGLE_ATTRIBUTES(TeamManager);
};

#endif // !__TEAM_MANAGER_H__

