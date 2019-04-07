#pragma once
#ifndef __BACKPACK_MANAGER_H__
#define __BACKPACK_MANAGER_H__
#include"tool/PreProcess.h"
#include"jsoncpp/value.h"
#include<thread>
#include<atomic>
#include<mutex>
#include<string>
#include<list>
#include<map>

struct ThingInfo
{
	std::string name = "";
	int type = NULL;
	int nums = 0;
	int grade = 1;

	bool operator==(const ThingInfo& info)
	{
		return (name == info.name&&type == info.type);
	}
};

class Slot;

#define AddToBackPack BackPackManager::getInstance()->addBackPackThing
#define RemoveFromBackPack BackPackManager::getInstance()->removeBackPackThing
#define BackPackMap BackPackManager::getInstance()->getBackPackMap

/*
*class BackPackManager
*背包管理器
*/
class BackPackManager:public cocos2d::CCObject
{
	GET_SINGLE_OBJECT(BackPackManager)
public:
	static std::map<std::string, int> TypeMaps;

	static void release();

	/*
	*addBackPackThing();
	*添加背包物品
	*/
	void addBackPackThing(ThingInfo thinginfo);

	/*
	*移除背包物品
	*removeBackPackThing();
	*@param name：物品名称
	*@return int：返回0表示没找到该物品，返回-1表示该物品减少一个，返回-2表示该物品减少到0
	*/
	int removeBackPackThing(const std::string& name, const int& count = 1);

	/*
	*getBackPackList()
	*获取背包物品内容
	*/
	const std::list<ThingInfo>& getBackPackMap();

	/*
	*int ThingNums(const std::string& name);
	*获取某物品数量
	*@param name ：物品名称1
	*@return int ：
	*/
	int ThingNums(const std::string& name);

	/*
	*readBackpackInfo();
	*读取角色背包信息
	*/
	void readBackpackInfo();

	void insertBackpackInfo(const ThingInfo& info);

	void dropThing(Json::Value& msg);
private:
	void updateBackpack(ThingInfo info);

	void deleteBackpack(ThingInfo info);

	BackPackManager();
	~BackPackManager();
	
	std::list<ThingInfo> m_backpackList;
	Slot* m_dropSlot;

	SINGLE_ATTRIBUTES(BackPackManager);
};
#endif // !__BACKPACK_MANAGER_H__

