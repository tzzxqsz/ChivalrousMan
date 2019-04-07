#include"NpcMonk.h"
#include"tool/GameData.h"
#include"tool/Commen.h"

DEF_REFLECT_FUNC(NpcMonk)

NpcMonk::NpcMonk()
{
	INIT_TALK_IN_NPC(NpcMonk);
	m_name = "NpcMonk";
}

NpcMonk::~NpcMonk()
{

}

void NpcMonk::collisionEvent()
{
	Npc::collisionEvent();
}