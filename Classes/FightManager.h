#pragma once
#ifndef __FIGHT_MANAGER_H__
#define __FIGHT_MANAGER_H__
#include"PreProcess.h"
#include"jsonCpp/value.h"

class FightManager :public cocos2d::CCObject
{
	GET_SINGLE_OBJECT(FightManager)
public:
	void c2sPlayerAtk(const std::string& skill,const int& grade,const int& dest,const int& towho);

	void c2sMonsterAtk(const int& dest, const int& who, const int& towho);

	void c2sPlayerRun(const int& dest, const int& flag);

	void c2sUseMedication(const int& dest);

	void c2sPlayerDie(const int& dest);

	void s2cPlayerAtk(Json::Value&);

	void s2cMonsterAtk(Json::Value&);

	void s2cPlayerRun(Json::Value&);

	void s2cUseMedication(Json::Value&);

	void s2cPlayerDie(Json::Value&);
private:
	FightManager();
	~FightManager();
	
	SINGLE_ATTRIBUTES(FightManager);
};

#endif // !__FIGHT_MANAGER_H__

