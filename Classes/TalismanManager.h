#pragma once
#ifndef __TALISMAN_MANAGER_H__
#define __TALISMAN_MANAGER_H__
#include"PreProcess.h"
#include<vector>

struct TalismanInfo 
{
	std::string name;
	int grade;
	float curExp;
	float exp;
	int isInBattle;
	int sort;

	TalismanInfo()
	{
		name = "";
		grade = 1;
		exp = 0;
		curExp = 0;
		isInBattle = 0;
	}

	bool operator<(const TalismanInfo& info)
	{
		if (isInBattle == info.isInBattle)
		{
			return sort < info.sort;
		}
		else
		{
			return isInBattle < info.isInBattle;
		}
	}
};

class TalismanManager:public cocos2d::CCObject
{
	GET_SINGLE_OBJECT(TalismanManager)
public:
	inline const std::vector<TalismanInfo>& getTalismanList();
private:
	void initTalismanList();

	TalismanManager();
	~TalismanManager();
	SINGLE_ATTRIBUTES(TalismanManager);

	std::vector<TalismanInfo> m_talismanList;
};

#endif // !__TALISMAN_MANAGER_H__

