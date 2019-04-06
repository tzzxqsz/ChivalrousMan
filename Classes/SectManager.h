#pragma once
#ifndef __SECT_MANAGER_H__
#define __SECT_MANAGER_H__
#include"PreProcess.h"
#include<vector>

struct Jingjie
{
	int name;
	float curexp;
	float exp;

	Jingjie()
	{
		name = -1;
		curexp = 0;
		exp = 500;
	}
};

class SectManager :public cocos2d::CCObject
{
	GET_SINGLE_OBJECT(SectManager);
public:
	static const int SECT_NUMS = 3;
	static const int LIMIT_LEVEL = 30;
	SectManager(const SectManager&) = delete;
	SectManager& operator=(const SectManager&) = delete;

	bool joinSect(const std::string& name);

	void learnGongfa(const std::string& name);

	std::string getGongfa();

	Jingjie getJingjie();

	std::string getJingjieName();

	std::string getGongfaName();

	bool addXiulianExp(float exp);
private:
	SectManager();
	~SectManager();

	void addXiulianExpEx(float exp);

	bool haveLearned(const std::string& name);

	void initData();

	std::vector<std::string> m_gongfas;
	Jingjie m_jingjie;
	SINGLE_ATTRIBUTES(SectManager);
};

#endif // !__SECT_MANAGER_H

