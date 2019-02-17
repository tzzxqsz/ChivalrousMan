#include"TeamManager.h"
#include"Commen.h"
#include"GameData.h"
#include"GameDynamicData.h"
#include"CameraPlayer.h"
#include"NetWorkManager.h"
#include"MessageConst.h"
#include"PlayerManager.h"
#include"GameUILayer.h"

DEFINE_SINGLE_ATTRIBUTES(TeamManager);

TeamManager::TeamManager()
{
	NetWorkManager::getInstance()->add(MESSAGE_TEAM_APPLY, handler(this, SEL_EVENTFUNC(TeamManager::s2cTeamApply)));
	NetWorkManager::getInstance()->add(MESSAGE_AGREE_TEAM, handler(this, SEL_EVENTFUNC(TeamManager::s2cAgreeTeam)));
	NetWorkManager::getInstance()->add(MESSAGE_REFUSE_TEAM, handler(this, SEL_EVENTFUNC(TeamManager::s2cRefuseTeam)));
	NetWorkManager::getInstance()->add(MESSAGE_DISSOLVE_TEAM, handler(this, SEL_EVENTFUNC(TeamManager::s2cTeamDissolve)));
	NetWorkManager::getInstance()->add(MESSAGE_TEAM_FIGHT, handler(this, SEL_EVENTFUNC(TeamManager::s2cTeamFight)));
	NetWorkManager::getInstance()->add(MESSAGE_TEAM_GOTO_MAP, handler(this, SEL_EVENTFUNC(TeamManager::s2cTeamGotoMap)));
	NetWorkManager::getInstance()->add(MESSAGE_TEAM_MOVE, handler(this, SEL_EVENTFUNC(TeamManager::s2cTeamMove)));
}

TeamManager::~TeamManager()
{
}

void TeamManager::release()
{
	RELEASE_NULL(m_instance);
}

void TeamManager::c2sTeamApply(const int& dest)
{
	NetMsg msg;
	msg["dest"] = dest;
	NetWorkManager::getInstance()->send(MESSAGE_TEAM_APPLY, msg);
}

void TeamManager::c2sRefuseTeam(const int& dest)
{
	std::map<std::string, std::string> msg;
	msg["dest"] = dest;
	m_applyTeamList.remove(dest);
	NetWorkManager::getInstance()->send(MESSAGE_REFUSE_TEAM, msg);
}

void TeamManager::c2sAgreeTeam(const int& dest)
{
	std::map<std::string, std::string> msg;
	msg["dest"] = NTS(dest);
	m_applyTeamList.remove(dest);
	NetWorkManager::getInstance()->send(MESSAGE_AGREE_TEAM, msg);
	createTeam(dest, P_STATUS_HEADER);
	CameraPlayer::getPlayerInstance()->setTeamStatus(P_STATUS_MEMBER);
}

void TeamManager::c2sTeamMove(cocos2d::Vec2 target, int dest)
{
	std::map<std::string, std::string> msg;
	msg["x"] = NTS(target.x);
	msg["y"] = NTS(target.y);
	msg["dest"] = NTS(dest);
	NetWorkManager::getInstance()->send(MESSAGE_TEAM_MOVE, msg);
}

void TeamManager::c2sTeamGotoMap(std::string map, cocos2d::Vec2 target, int dest)
{
	std::map<std::string, std::string> msg;
	msg["dest"] = NTS(dest);
	msg["map"] = map;
	msg["x"] = NTS(target.x);
	msg["y"] = NTS(target.y);
	NetWorkManager::getInstance()->send(MESSAGE_TEAM_GOTO_MAP, msg);
}

void TeamManager::c2sTeamDissolve(const int & dest)
{
	std::map<std::string, std::string> msg;
	msg["dest"] = NTS(dest);
	NetWorkManager::getInstance()->send(MESSAGE_DISSOLVE_TEAM, msg);
}

void TeamManager::c2sTeamFight(int dest, std::string name, int nums)
{
	std::map<std::string, std::string> msg;
	msg["dest"] = NTS(dest);
	msg["name"] = name;
	msg["nums"] = NTS(nums);
	NetWorkManager::getInstance()->send(MESSAGE_TEAM_FIGHT, msg);
}

void TeamManager::s2cTeamApply(Json::Value & msg)
{
	m_applyTeamList.push_back(msg["fd"].asInt());
	if (m_applyTeamList.size() > 6)
	{
		m_applyTeamList.pop_front();
	}
	auto gameUIlayer = cocos2d::Director::sharedDirector()->getRunningScene()->getChildByName("GameUILayer");
	if (gameUIlayer!=nullptr)
	{
		dynamic_cast<GameUILayer*>(gameUIlayer)->setTeamSpot(true);
	}
}

void TeamManager::s2cRefuseTeam(Json::Value & msg)
{
	std::string name = PlayerManager::getInstance()->findRoleNameByFd(msg["fd"].asInt());
	SetIntData("IsHaveTip", 1);
	SetStringData("TipText", name + StringValue("RefuseText"));
}

void TeamManager::s2cAgreeTeam(Json::Value & msg)
{
	int fd = msg["fd"].asInt();
	std::string name = PlayerManager::getInstance()->findRoleNameByFd(fd);
	SetIntData("IsHaveTip", 1);
	SetStringData("TipText", name + StringValue("AgreeText"));
	CameraPlayer::getPlayerInstance()->setTeamStatus(P_STATUS_HEADER);
	createTeam(fd, P_STATUS_MEMBER);
}

void TeamManager::s2cTeamMove(Json::Value & msg)
{
	CameraPlayer::getPlayerInstance()->moveTo(Vec2{ msg["x"].asFloat(),msg["y"].asFloat() }, 1);
}

void TeamManager::s2cTeamGotoMap(Json::Value &msg)
{
	if (CCDirector::getInstance()->getRunningScene()->getName() == "GameScene")
	{
		TeamGotoMap_Msg tmsg;
		tmsg.x = msg["x"].asFloat();
		tmsg.y = msg["y"].asFloat();
		strcpy_s(tmsg.map, msg["map"].asCString());
		m_gotoMapMsgs.push_back(tmsg);
	}
}

void TeamManager::s2cTeamDissolve(Json::Value &)
{
	dissolveTeam();
	SetIntData("IsHaveTip", 1);
	SetStringData("TipText", StringValue("TeamDissolveText"));
}

void TeamManager::s2cTeamFight(Json::Value & msg)
{
	if (cocos2d::Director::getInstance()->getRunningScene()->getName() == "GameScene")
	{
		SetIntData("IsEntryFight", 1);
		SetIntData("MonsterNums", msg["nums"].asInt());
		SetStringData("MonsterName", msg["name"].asString());
	}
}

void TeamManager::createTeam(const int& fd, int status)
{
	m_teamMembers.clear();
	m_teamMembers[fd] = status;
}

void TeamManager::removeTeamMembers(int fd)
{
	int iRet = m_teamMembers.erase(fd);
	if (iRet)
	{
		if (m_teamMembers.size() == 0)
		{
			CameraPlayer::getPlayerInstance()->setTeamStatus(P_STATUS_NORMAL);
		}
	}
}

void TeamManager::dissolveTeam()
{
	m_teamMembers.clear();
	CameraPlayer::getPlayerInstance()->setTeamStatus(P_STATUS_NORMAL);
}