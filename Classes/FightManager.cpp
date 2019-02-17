#include"FightManager.h"
#include"NetWorkManager.h"
#include"MessageConst.h"
#include"GameData.h"
#include"FightLayer.h"

DEFINE_SINGLE_ATTRIBUTES(FightManager);

FightManager::FightManager()
{
	NetWorkManager::getInstance()->add(MESSAGE_PLAYER_ATTACK, handler(this, SEL_EVENTFUNC(FightManager::s2cPlayerAtk)));
	NetWorkManager::getInstance()->add(MESSAGE_MONSTER_ATTACK, handler(this, SEL_EVENTFUNC(FightManager::s2cMonsterAtk)));
	NetWorkManager::getInstance()->add(MESSAGE_PLAYER_DIE, handler(this, SEL_EVENTFUNC(FightManager::s2cPlayerDie)));
	NetWorkManager::getInstance()->add(MESSAGE_PLAYER_RUN, handler(this, SEL_EVENTFUNC(FightManager::s2cPlayerRun)));
	NetWorkManager::getInstance()->add(MESSAGE_USE_MEDICATION, handler(this, SEL_EVENTFUNC(FightManager::s2cUseMedication)));
}

FightManager::~FightManager()
{
}

void FightManager::c2sPlayerAtk(const std::string& skill, const int& grade, const int& dest, const int& towho)
{
	NetMsg msg;
	msg["fd"] = NTS(-1);
	msg["grade"] = NTS(grade);
	msg["dest"] = NTS(dest);
	msg["skill"] = skill;
	msg["towho"] = NTS(towho);
	NetWorkManager::getInstance()->send(MESSAGE_PLAYER_ATTACK, msg);
}

void FightManager::c2sMonsterAtk(const int & dest, const int & who, const int & towho)
{
	NetMsg msg;
	msg["dest"] = NTS(dest);
	msg["fd"] = NTS(-1);
	msg["who"] = NTS(who);
	msg["towho"] = NTS(towho);
	NetWorkManager::getInstance()->send(MESSAGE_MONSTER_ATTACK, msg);
}

void FightManager::c2sPlayerRun(const int & dest, const int & flag)
{
	NetMsg msg;
	msg["dest"] = NTS(dest);
	msg["flag"] = NTS(flag);
	NetWorkManager::getInstance()->send(MESSAGE_PLAYER_RUN, msg);
}

void FightManager::c2sUseMedication(const int & dest)
{
	NetMsg msg;
	msg["dest"] = NTS(dest);
	NetWorkManager::getInstance()->send(MESSAGE_USE_MEDICATION, msg);
}

void FightManager::c2sPlayerDie(const int & dest)
{
	NetMsg msg;
	msg["dest"] = NTS(dest);
	NetWorkManager::getInstance()->send(MESSAGE_PLAYER_DIE, msg);
}

void FightManager::s2cPlayerAtk(Json::Value & msg)
{
	auto ftLayer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("FightLayer");
	if (ftLayer != nullptr)
	{
		dynamic_cast<FightLayer*>(ftLayer)->otherPlayerAtk(msg["fd"].asInt(), msg["skill"].asString(), msg["grade"].asInt(), msg["towho"].asInt());
	}
}

void FightManager::s2cMonsterAtk(Json::Value & msg)
{
	auto ftLayer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("FightLayer");
	if (ftLayer != nullptr)
	{
		int towho;
		if (msg["towho"].asInt() == -1)
		{
			towho = ((FightLayer*)ftLayer)->findOtherPlayerIndexByFd(msg["fd"].asInt());
		}
		else
		{
			towho = ((FightLayer*)ftLayer)->findOtherPlayerIndexByFd(msg["towho"].asInt());
		}
		((FightLayer*)ftLayer)->monsterAttackPlayer(msg["towho"].asInt(), towho);
	}
}

void FightManager::s2cPlayerRun(Json::Value & msg)
{
	auto ftLayer =cocos2d::Director::getInstance()->getRunningScene()->getChildByName("FightLayer");
	if (ftLayer != nullptr)
	{
		dynamic_cast<FightLayer*>(ftLayer)->OtherRunAway(msg["flag"].asInt());
	}
}

void FightManager::s2cUseMedication(Json::Value &)
{
	auto ftLayer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("FightLayer");
	if (ftLayer != nullptr)
		dynamic_cast<FightLayer*>(ftLayer)->setOtherPalyerEnd();
}

void FightManager::s2cPlayerDie(Json::Value&)
{
	auto ftLayer =cocos2d::Director::getInstance()->getRunningScene()->getChildByName("FightLayer");
	if (ftLayer != nullptr)
		dynamic_cast<FightLayer*>(ftLayer)->setOtherPlayerDie();
}

