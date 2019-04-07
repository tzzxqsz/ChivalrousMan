#pragma once
#ifndef __TALISMAN_MANAGER_H__
#define __TALISMAN_MANAGER_H__
#include"tool/PreProcess.h"
#include<vector>

struct TalismanInfo 
{
	std::string name;
	int grade;
	float curExp;
	float exp;
	int isInBattle;
	int sort;
	int have;

	TalismanInfo()
	{
		name = "";
		grade = 1;
		exp = 0;
		curExp = 0;
		isInBattle = 0;
		have = 0;
	}

	bool operator<(const TalismanInfo& info)
	{
		if (have == info.have)
		{
			if (isInBattle == info.isInBattle)
				return sort < info.sort;
			else
				return isInBattle > info.isInBattle;
		}
		else
		{
			return have > info.have;
		}
	}
};

class Playermw;

class TalismanManager:public cocos2d::CCObject
{
	GET_SINGLE_OBJECT(TalismanManager)
public:
	const std::vector<TalismanInfo>& getTalismanList();

	TalismanInfo getTalismanInfo(const int& index);

	int getTalismanSize();

	void mergeTalismanInfo();

	void synthesisTalisman(const int& index);

	void upTalisman(const int& index, const int& value);

	void battleTalisman(const int& index, const int& isBattle);

	int battleNums();

	std::vector<TalismanInfo> getBattleTalisman();
private:
	void upTalismanEx(const int& index, const int& value);

	void initTalismanList();

	void mergeInfo(Playermw& info);

	TalismanManager();
	~TalismanManager();
	SINGLE_ATTRIBUTES(TalismanManager);

	std::vector<TalismanInfo> m_talismanList;
};

#endif // !__TALISMAN_MANAGER_H__

