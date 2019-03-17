#include"BackPackManager.h"
#include"Commen.h"
#include"Model.h"
#include"DBDao.h"
#include"GameData.h"
#include"GameDynamicData.h"
#include"SignalConst.h"
#include"SignalManager.h"
#include<utility>
#include<map>

DEFINE_SINGLE_ATTRIBUTES(BackPackManager);
std::map<std::string, int> BackPackManager::TypeMaps;


BackPackManager::BackPackManager()
{
	TypeMaps["talisman"] = MW_FRAGMENT;
	TypeMaps["equipment"] = EQUIPMENT;
	TypeMaps["medication"] = MEDICATION;

	m_dropSlot = SignalManager::getInstance()->add(EVENT_DROP_THING, handler(this, SEL_EVENTFUNC(BackPackManager::dropThing)));
}

BackPackManager::~BackPackManager()
{
	m_dropSlot->remove();
}

void BackPackManager::release()
{
	RELEASE_NULL(m_instance);
}

void BackPackManager::addBackPackThing(ThingInfo thinginfo)
{
	int flag = 0;
	for (auto it = m_backpackList.begin(); it != m_backpackList.end(); ++it)
	{
		if (it->name == thinginfo.name)
		{
			flag = 1;
			++it->nums;
			updateBackpack(*it);
		}
	}
	if (!flag)
	{
		thinginfo.nums = 1;
		m_backpackList.push_back(thinginfo);
		insertBackpackInfo(thinginfo);
	}
}

int BackPackManager::removeBackPackThing(const std::string& name)
{
	for (auto it = m_backpackList.begin(); it != m_backpackList.end(); ++it)
	{
		if (it->name == name)
		{
			--(it->nums);
			if (it->nums == 0)
			{
				deleteBackpack(*it);
				m_backpackList.erase(it);
				return -2;
			}
			updateBackpack(*it);
			return -1;
		}
	}
	return 0;
}

const std::list<ThingInfo>& BackPackManager::getBackPackMap()
{
	return m_backpackList;
}

int BackPackManager::ThingNums(const std::string& name)
{
	for (auto var : m_backpackList)
	{
		if (var.name == name)
		{
			return var.nums;
		}
	}
	return 0;
}

void BackPackManager::readBackpackInfo()
{
	m_backpackList.clear();
	BackPack info;
	DBDao<BackPack> dao;
	info.setplayername(GetStringData("playername"));
	info.setrolename(GetStringData("rolename"));
	dao.setModel(info);
	auto list = dao.queryModel();
	for (auto var : list)
	{
		ThingInfo info;
		info.grade = std::stoi(var.getthinggrade());
		info.name = var.getthingname();
		info.nums = std::stoi(var.getthingnums());
		info.type = std::stoi(var.getthingtype());
		m_backpackList.push_back(info);
	}
}

void BackPackManager::insertBackpackInfo(const ThingInfo& info)
{
	BackPack data;
	DBDao<BackPack> dao;
	data.setplayername(GetStringData("playername"));
	data.setrolename(GetStringData("rolename"));
	data.setthinggrade(NTS(info.grade));
	data.setthingname(info.name);
	data.setthingnums(NTS(info.nums));
	data.setthingtype(NTS(info.type));
	dao.setModel(data);
	dao.insertModel();
}

void BackPackManager::dropThing(Json::Value & msg)
{
	if (msg["name"].asString() == "empty")
	{
		return;
	}
	ThingInfo info;
	info.name = msg["name"].asString();
	info.type = TypeMaps[msg["type"].asString()];
	info.nums = 1;
	info.grade = 0;
	addBackPackThing(info);
}

void BackPackManager::updateBackpack(ThingInfo info)
{
	BackPack thing;
	DBDao<BackPack> dao;
	thing.setthingnums(NTS(info.nums));
	std::map<std::string, std::string> keyvls;
	keyvls["playername"] = GetStringData("playername");
	keyvls["rolename"] = GetStringData("rolename");
	keyvls["thingname"] = info.name;
	dao.setModel(thing);
	dao.updateModel(keyvls);
}

void BackPackManager::deleteBackpack(ThingInfo info)
{
	BackPack thing;
	DBDao<BackPack> dao;
	thing.setthingname(info.name);
	thing.setplayername(GetStringData("playername"));
	thing.setrolename(GetStringData("rolename"));
	dao.setModel(thing);
	dao.deleteModel();
}