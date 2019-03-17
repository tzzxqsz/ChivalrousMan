#include"TalismanManager.h"
#include<fstream>
#include<sstream>
#include<algorithm>
#include"Path.h"
#include"GameData.h"
#include"jsonCpp\reader.h"
#include"jsonCpp\value.h"
#include"DBDao.h"
#include"Model.h"

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
			var.have = true;
		}
	}
}

TalismanManager::TalismanManager()
{
	initTalismanList();
}

TalismanManager::~TalismanManager()
{
	
}