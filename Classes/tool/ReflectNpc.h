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
*������������Npc����
*/
class ReflectNpc
{
	GET_SINGLE_OBJECT(ReflectNpc)
	CLASS_ESSENTAIL(ReflectNpc)
public:
	/*
	* registerReflectClass(const std::string& classname, Sel_NpcCallFunc callfunc);
	*ע�ᷴ��ص�����
	*@param classname:��Ҫ���������
	*@param callfunc:����ص�����
	*/
	void registerReflectClass(const std::string& classname, Sel_NpcCallFunc callfunc);

	/*
	*getReflectObject(const std::string& classname);
	*��ȡ����Ķ���
	*@param classname:���������
	*/
	Npc* getReflectObject(const std::string& classname);

	static void release();
private:
	SINGLE_ATTRIBUTES(ReflectNpc);

	std::map<std::string, Sel_NpcCallFunc> m_reflectMap;
};

#endif // !__REFLECT_NPC_H__

