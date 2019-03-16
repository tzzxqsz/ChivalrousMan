#include"TalismanManager.h"
#include<fstream>
#include<sstream>
#include<algorithm>
#include"Path.h"
#include"GameData.h"
#include"jsonCpp\reader.h"
#include"jsonCpp\value.h"

DEFINE_SINGLE_ATTRIBUTES(TalismanManager);

inline const std::vector<TalismanInfo>& TalismanManager::getTalismanList()
{
	return m_talismanList;
}

void TalismanManager::initTalismanList()
{
	std::ifstream ifs;
	ifs.open(getTalismanPurePath("1_Talisman.cfg"));
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
			m_talismanList.push_back(info);
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