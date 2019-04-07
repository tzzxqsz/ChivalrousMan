#include"NpcManmom.h"
#include"tool/GameData.h"
#include"tool/Commen.h"

DEF_REFLECT_FUNC(NpcMamom)

NpcMamom::NpcMamom()
{
	INIT_TALK_IN_NPC(NpcMamom);
	m_name = "NpcMamom";
}
 
NpcMamom::~NpcMamom()
{

}

void NpcMamom::collisionEvent()
{
	Npc::collisionEvent();
}