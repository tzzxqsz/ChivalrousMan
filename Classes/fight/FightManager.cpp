#include"FightManager.h"
#include"net/NetWorkManager.h"
#include"net/MessageConst.h"
#include"tool/GameData.h"
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
	msg["fd"] = -1;
	msg["grade"] = grade;
	msg["dest"] = dest;
	msg["skill"] = skill;
	msg["towho"] = towho;
	NetWorkManager::getInstance()->send(MESSAGE_PLAYER_ATTACK, msg);
}

void FightManager::c2sMonsterAtk(const int & dest, const int & who, const int & towho)
{
	NetMsg msg;
	msg["dest"] = dest;
	msg["fd"] = -1;
	msg["who"] = who;
	msg["towho"] = towho;
	NetWorkManager::getInstance()->send(MESSAGE_MONSTER_ATTACK, msg);
}

void FightManager::c2sPlayerRun(const int & dest, const int & flag)
{
	NetMsg msg;
	msg["dest"] = dest;
	msg["flag"] = flag;
	NetWorkManager::getInstance()->send(MESSAGE_PLAYER_RUN, msg);
}

void FightManager::c2sUseMedication(const int & dest)
{
	NetMsg msg;
	msg["dest"] = dest;
	NetWorkManager::getInstance()->send(MESSAGE_USE_MEDICATION, msg);
}

void FightManager::c2sPlayerDie(const int & dest)
{
	NetMsg msg;
	msg["dest"] = dest;
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
		 ((FightLayer*)ftLayer)->monsterAttackPlayer(msg["who"].asInt(), towho);
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

