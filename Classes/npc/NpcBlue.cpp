#include"NpcBlue.h"
#include"tool/GameData.h"
#include"tool/Commen.h"

DEF_REFLECT_FUNC(NpcBlue)
  
NpcBlue::NpcBlue()
{
    INIT_TALK_IN_NPC(NpcBlue);
	m_name = "NpcBlue";
}
  
NpcBlue::~NpcBlue()
{

}

void NpcBlue::collisionEvent()
{
	Npc::collisionEvent();
}
