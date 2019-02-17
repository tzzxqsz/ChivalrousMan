#include"PlayerManager.h"
#include"MessageConst.h"
#include"GameDynamicData.h"
#include"CameraPlayer.h"
#include"NetWorkManager.h"
#include"GameScene.h"
#include"ObjectLayer.h"
#include"GameData.h"
#include"FightLayer.h"
#include"TeamManager.h"
#include"TalkManager.h"

DEFINE_SINGLE_ATTRIBUTES(PlayerManager);

PlayerManager::PlayerManager()
{
	NetWorkManager::getInstance()->add(MESSAGE_INIT_DATA, handler(this, SEL_EVENTFUNC(PlayerManager::s2cInitPlayerData)));
	NetWorkManager::getInstance()->add(MESSAGE_INIT_POS, handler(this, SEL_EVENTFUNC(PlayerManager::s2cInitPos)));
	NetWorkManager::getInstance()->add(MESSAGE_MOVE_TO, handler(this, SEL_EVENTFUNC(PlayerManager::s2cMoveTo)));
	NetWorkManager::getInstance()->add(MESSAGE_PLAYER_LEAVE, handler(this, SEL_EVENTFUNC(PlayerManager::s2cPlayerLeave)));
	NetWorkManager::getInstance()->add(MESSAGE_UPDATE_DATA, handler(this, SEL_EVENTFUNC(PlayerManager::s2cUpdatePlayerData)));
	NetWorkManager::getInstance()->add(MESSAGE_VERIFY_POS, handler(this, SEL_EVENTFUNC(PlayerManager::s2cVerifyPlayerPos)));
}

PlayerManager::~PlayerManager()
{

}

void PlayerManager::c2sInitPlayerData()
{
	std::map<std::string, std::string> msg;
	m_playerlist.clear();
	msg["playername"] = GetStringData("playername");
	msg["rolename"] = GetStringData("rolename");
	msg["playertype"] = GetStringData("PlayerType");
	msg["curmap"] = NTS(GetIntData("CurMap"));
	msg["attack"] = NTS(GetPlayerData().getattack());
	msg["blood"] = NTS(GetPlayerData().getblood());
	msg["defense"] = NTS(GetPlayerData().getdefense());
	msg["mana"] = NTS(GetPlayerData().getmana());
	msg["grade"] = NTS(GetPlayerData().getgrade());
	msg["fd"] = NTS(-1);
	NetWorkManager::getInstance()->send(MESSAGE_INIT_DATA, msg);
}

void PlayerManager::c2sInitPos()
{
	std::map<std::string, std::string> msg;
	msg["x"] = NTS(PlayerPos.x);
	msg["y"] = NTS(PlayerPos.y);
	msg["fd"] = NTS(-1);
	msg["curmap"] = GetIntData("CurMap");
	NetWorkManager::getInstance()->send(MESSAGE_INIT_POS, msg);
}

void PlayerManager::c2sMoveTo(const cocos2d::Vec2 & pos, int less)
{
	std::map<std::string, std::string> msg;
	msg["fd"] = NTS(-1);
	msg["x"] = NTS(pos.x);
	msg["y"] = NTS(pos.y);
	msg["less"] = less;
	NetWorkManager::getInstance()->send(MESSAGE_MOVE_TO, msg);
}

void PlayerManager::c2sPlayerLeave()
{
	std::map<std::string, std::string> msg;
	msg["fd"] = NTS(-1);
	NetWorkManager::getInstance()->send(MESSAGE_PLAYER_LEAVE, msg);
}

void PlayerManager::c2sVerifyPlayerPos()
{
	std::map<std::string, std::string> msg;
	msg["x"] = NTS(PlayerPos.x);
	msg["y"] = NTS(PlayerPos.y);
	msg["fd"] = NTS(-1);
	NetWorkManager::getInstance()->send(MESSAGE_VERIFY_POS, msg);
}

void PlayerManager::c2sUpdatePlayerData()
{
	std::map<std::string, std::string> msg;
	msg["attack"] = NTS(GetPlayerData().getattack());
	msg["blood"] = NTS(GetPlayerData().getblood());
	msg["defense"] = NTS(GetPlayerData().getdefense());
	msg["fd"] = NTS(-1);
	msg["grade"] = NTS(GetPlayerData().getgrade());
	msg["mana"] = NTS(GetPlayerData().getmana());
	NetWorkManager::getInstance()->send(MESSAGE_UPDATE_DATA, msg);
}

void PlayerManager::s2cInitPlayerData(Json::Value & msg)
{
	Player_Info pinfo;
	pinfo.playername = msg["playername"].asString();
	pinfo.attack = msg["attack"].asFloat();
	pinfo.blood = msg["blood"].asFloat();
	pinfo.curmap = msg["curmap"].asInt();
	pinfo.defense = msg["defense"].asFloat();
	pinfo.mana = msg["mana"].asFloat();
	pinfo.playertype = msg["playertype"].asString();
	pinfo.rolename = msg["rolename"].asString();
	pinfo.fd = msg["fd"].asInt();
	pinfo.grade = msg["grade"].asInt();
	m_playerlist.push_back(pinfo);
}

void PlayerManager::s2cInitPos(Json::Value & msg)
{
	for (auto var = m_playerlist.begin(); var != m_playerlist.end(); ++var)
	{
		if (msg["fd"].asInt() == var->fd)
		{
			var->x = msg["x"].asFloat();
			var->y = msg["y"].asFloat();
			var->curmap = msg["curmap"].asInt();
			if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName("ObjectLayer") != nullptr)
				CurGameScene()->getObjectLayer()->addPlayer(*var);
		}
	}
}

void PlayerManager::s2cPlayerLeave(Json::Value & msg)
{
	removePlayer(msg["fd"].asInt());
	auto ftLayer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("FightLayer");
	if (ftLayer != nullptr)
		dynamic_cast<FightLayer*>(ftLayer)->OtherPlayerLeave();
}

void PlayerManager::s2cMoveTo(Json::Value & msg)
{
	cocos2d::Vec2 target{ msg["x"].asFloat() ,msg["y"].asFloat() };
	for (auto var : m_playerlist)
	{
		if (var.fd == msg["fd"].asInt())
		{
			if (GetIntData("IsHaveGameScene") == 1)
				CurGameScene()->getObjectLayer()->moveOtherPlayer(var.playername, var.rolename, target, msg["less"].asInt());
		}
	}
}

void PlayerManager::s2cVerifyPlayerPos(Json::Value & msg)
{
	for (auto var = m_playerlist.begin(); var != m_playerlist.begin(); ++var)
	{
		if (var->fd == msg["fd"].asInt())
		{
			var->x = msg["x"].asFloat();
			var->y = msg["y"].asFloat();
			if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName("ObjectLayer") != nullptr)
				CurGameScene()->getObjectLayer()->verifyPlayerPos(var->playername, var->rolename, cocos2d::Vec2{ var->x,var->y });
		}
	}
}

void PlayerManager::s2cUpdatePlayerData(Json::Value & msg)
{
	for (auto var = m_playerlist.begin(); var != m_playerlist.end(); ++var)
	{
		if (var->fd == msg["fd"].asInt())
		{
			var->attack = msg["attack"].asFloat();
			var->defense = msg["defense"].asFloat();
			var->blood = msg["blood"].asFloat();
			var->grade = msg["grade"].asFloat();
			var->mana = msg["mana"].asFloat();
			if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName("ObjectLayer") != nullptr)
				CurGameScene()->getObjectLayer()->updatePlayerData(var->playername, var->rolename, *var);
		}
	}
}

void PlayerManager::removePlayer(int fd)
{
	for (auto it = m_playerlist.begin(); it != m_playerlist.end(); ++it)
	{
		if (it->fd == fd)
		{
			if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName("ObjectLayer") != nullptr)
				CurGameScene()->getObjectLayer()->removePlayer(it->playername, it->rolename);
			TeamManager::getInstance()->removeTeamMembers(it->fd);
			TalkManager::getInstance()->removePrivateMsg(it->fd);
			m_playerlist.erase(it);
			return;
		}
	}
}

std::string PlayerManager::findRoleNameByFd(const int & fd)
{
	for (auto var : m_playerlist)
	{
		if (var.fd == fd)
		{
			return var.rolename;
		}
	}
	return "";
}

Player_Info PlayerManager::findPlayerInfoByFd(const int & fd)
{
	Player_Info info;
	for (const auto& var : m_playerlist)
	{
		if (var.fd == fd)
		{
			return var;
		}
	}
	return info;
}
