#pragma once
#ifndef __PLAYER_DATA_H__
#define __PLAYER_DATA_H__
#include"tool/PreProcess.h"

/*
*保存玩家数据
*/
class PlayerData
{
public:
	PlayerData();
	~PlayerData();

	/*
	*增加金币
	*/
	void addGlod(const float& vl);

	/*
	*减少金币
	*/
	float subGlod(const float& vl);

	/*
	*增加经验
	*/
	void addExp(const float& vl);

	/*
	*增加当前血量
	*/
	void addcurBlood(const float& vl);

	/*
	*减少当前的血量
	*/
	void subcurBlood(const float& vl);

	/*
	*增加当前的魔法
	*/
	void addcurMana(const float& vl);

	/*
	*减少当前的魔法
	*/
	void subcurMana(const float& vl);

	/*
	*升级
	*/
	void upGrade();

	//增加人物属性
	void addProperty(float blood, float mana, float attack, float defense);

	PROPERTY__REF(float, m_glod, glod)
	PROPERTY__REF(float, m_grade, grade)
	PROPERTY__REF(float, m_blood, blood)
	PROPERTY__REF(float, m_mana, mana)
	PROPERTY__REF(float, m_attack, attack)
	PROPERTY__REF(float, m_defense, defense)
	PROPERTY__REF(float, m_speed, speed)
	PROPERTY__REF(float,m_exp,exp)
	PROPERTY__REF(float,m_maxExp,maxExp)
	PROPERTY__REF(float,m_curblood,curblood)
	PROPERTY__REF(float,m_curmana,curmana)
	PROPERTY__REF(std::string,playername,playername)
	PROPERTY__REF(std::string,rolename, rolename)
	PROPERTY__REF(std::string,roleType, roleType)
	PROPERTY__REF(std::string, sect, Sect)
	PROPERTY__REF(std::string, gongfa, GongFa)
	PROPERTY__REF(std::string, jingjie, JingJie)
};

#endif // !__PLAYER_DATA_H__

