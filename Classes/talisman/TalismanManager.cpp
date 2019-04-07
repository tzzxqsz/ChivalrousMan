#include"TalismanManager.h"
#include<fstream>
#include<sstream>
#include<algorithm>
#include"tool/Path.h"
#include"tool/GameData.h"
#include"jsonCpp\reader.h"
#include"jsonCpp\value.h"
#include"tool/GameDynamicData.h"
#include"dbconnect/DBDao.h"
#include"dbconnect/Model.h"
#include"player/CameraPlayer.h"
#include<map>

DEFINE_SINGLE_ATTRIBUTES(TalismanManager);

const std::vector<TalismanInfo>& TalismanManager::getTalismanList()
{
	return m_talismanList;
}

TalismanInfo TalismanManager::getTalismanInfo(const int & index)
{
	return m_talismanList.at(index);
}

int TalismanManager::getTalismanSize()
{
	return m_talismanList.size();
}

void TalismanManager::mergeTalismanInfo()
{
	DBDao<Playermw> db;
	auto list = db.queryModel();
	for (auto& var : list)
	{
		mergeInfo(var);
	}
	std::sort(m_talismanList.begin(), m_talismanList.end());
}

void TalismanManager::synthesisTalisman(const int & index)
{
	m_talismanList[index].have = true;
	DBDao<Playermw> db;
	Playermw mw;
	mw.setplayername(GetPlayerData().getplayername());
	mw.setrolename(GetPlayerData().getrolename());
	mw.setcurexp("0");
	mw.setexp(NTS(m_talismanList[index].grade * 200));
	mw.setgrade("1");
	mw.setIs_in_battle("0");
	mw.setmw_name(m_talismanList[index].name);
	db.setModel(mw);
	db.insertModel();
	m_talismanList[index].isInBattle = 0;
	m_talismanList[index].curExp = 0;
	m_talismanList[index].exp = m_talismanList[index].grade * 200;
}

void TalismanManager::upTalisman(const int & index, const int & value)
{
	upTalismanEx(index, value);
	DBDao<Playermw> db;
	Playermw mw;
	mw.setcurexp(NTS(m_talismanList[index].curExp));
	mw.setexp(NTS(m_talismanList[index].grade * 200));
	mw.setgrade(NTS(m_talismanList[index].grade));
	db.setModel(mw);
	std::map<std::string, std::string> kvls;
	kvls["playername"] = GetPlayerData().getplayername();
	kvls["rolename"] = GetPlayerData().getrolename();
	db.setModel(mw);
	db.updateModel(kvls);
}

void TalismanManager::battleTalisman(const int & index, const int & isBattle)
{
	m_talismanList[index].isInBattle = isBattle;
	DBDao<Playermw> db;
	Playermw mw;
	mw.setIs_in_battle(NTS(isBattle));
	db.setModel(mw);
	std::map<std::string, std::string> kvls;
	kvls["playername"] = GetPlayerData().getplayername();
	kvls["rolename"] = GetPlayerData().getrolename();
	kvls["mw_name"] = m_talismanList[index].name;
	db.setModel(mw);
	db.updateModel(kvls);
}

int TalismanManager::battleNums()
{
	int count = 0;
	for (auto& var : m_talismanList)
	{
		if (var.isInBattle)
		{
			++count;
		}
	}
	return count;
}

std::vector<TalismanInfo> TalismanManager::getBattleTalisman()
{
	std::vector<TalismanInfo> infos;
	for (const auto & var : m_talismanList)
	{
		if (var.isInBattle)
			infos.push_back(var);
	}
	return infos;
}

void TalismanManager::upTalismanEx(const int & index, const int & value)
{
	m_talismanList[index].curExp += value;
	int curExp = m_talismanList[index].curExp;
	int exp = m_talismanList[index].exp;
	if (curExp > exp)
	{
		m_talismanList[index].grade++;
		m_talismanList[index].curExp = 0;
		m_talismanList[index].exp = m_talismanList[index].grade * (200 + m_talismanList[index].grade * 30);
		upTalisman(index, curExp - exp);
	}
}

void TalismanManager::initTalismanList()
{
	std::ifstream ifs;
	ifs.open(getTalismanPurePath("1_Talismain.cfg"));
	std::stringstream ss;
	ss << ifs.rdbuf();
	ifs.close();
	std::string str;
	ss >> str;
	
	Json::Reader reader;
	Json::Value value;
	if (reader.parse(str, value))
	{
		int nums = value["nums"].asInt();
		for (int i = 1; i <= nums; ++i)
		{
			TalismanInfo info;
			info.name = value[NTS(i)].asString();
			info.sort = i;
			m_talismanList.push_back(info);
		}
	}
}

void TalismanManager::mergeInfo(Playermw & info)
{
	for (auto& var : m_talismanList)
	{
		if (var.name == info.getmw_name())
		{
			var.grade = std::stoi(info.getgrade());
			var.curExp = std::stof(info.getcurexp());
			var.exp = std::stof(info.getexp());
			var.isInBattle = std::stoi(info.getIs_in_battle());
			var.have = 1;
		}
	}
}

TalismanManager::TalismanManager()
{
	initTalismanList();
	mergeTalismanInfo();
}

TalismanManager::~TalismanManager()
{
	
}