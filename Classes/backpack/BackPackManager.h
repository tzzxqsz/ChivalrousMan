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
*����������
*/
class BackPackManager:public cocos2d::CCObject
{
	GET_SINGLE_OBJECT(BackPackManager)
public:
	static std::map<std::string, int> TypeMaps;

	static void release();

	/*
	*addBackPackThing();
	*��ӱ�����Ʒ
	*/
	void addBackPackThing(ThingInfo thinginfo);

	/*
	*�Ƴ�������Ʒ
	*removeBackPackThing();
	*@param name����Ʒ����
	*@return int������0��ʾû�ҵ�����Ʒ������-1��ʾ����Ʒ����һ��������-2��ʾ����Ʒ���ٵ�0
	*/
	int removeBackPackThing(const std::string& name, const int& count = 1);

	/*
	*getBackPackList()
	*��ȡ������Ʒ����
	*/
	const std::list<ThingInfo>& getBackPackMap();

	/*
	*int ThingNums(const std::string& name);
	*��ȡĳ��Ʒ����
	*@param name ����Ʒ����1
	*@return int ��
	*/
	int ThingNums(const std::string& name);

	/*
	*readBackpackInfo();
	*��ȡ��ɫ������Ϣ
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

