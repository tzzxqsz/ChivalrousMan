#pragma once
#ifndef __REFLECT_NPC_H__
#define __REFLECT_NPC_H__
#include"PreProcess.h"
#include"npc/NpcBlue.h"
#include"npc/NpcEquip.h"
#include"npc/NpcManmom.h"
#include"npc/NpcMonk.h"
#include"npc/NpcPink.h"
#include"npc/NpcSkill.h"
#include"npc/NpcVallige.h"
#include<map>
#include<string>

class Npc;

typedef Npc* (*Sel_NpcCallFunc)();

/*
*ReflectNpc
*根据类名反射Npc对象
*/
class ReflectNpc
{
	GET_SINGLE_OBJECT(ReflectNpc)
	CLASS_ESSENTAIL(ReflectNpc)
public:
	/*
	* registerReflectClass(const std::string& classname, Sel_NpcCallFunc callfunc);
	*注册反射回调函数
	*@param classname:需要反射的类名
	*@param callfunc:反射回调函数
	*/
	void registerReflectClass(const std::string& classname, Sel_NpcCallFunc callfunc);

	/*
	*getReflectObject(const std::string& classname);
	*获取反射的对象
	*@param classname:反射的类名
	*/
	Npc* getReflectObject(const std::string& classname);

	static void release();
private:
	SINGLE_ATTRIBUTES(ReflectNpc);

	std::map<std::string, Sel_NpcCallFunc> m_reflectMap;
};

#endif // !__REFLECT_NPC_H__

