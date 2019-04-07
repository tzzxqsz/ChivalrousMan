#include"NpcVallige.h"
#include"GameScene.h"
#include"tool/GameData.h"
#include"tool/GameDynamicData.h"
#include"talk/TalkLayer.h"
#include"tool/Commen.h"

DEF_REFLECT_FUNC(NpcVallige)

NpcVallige::NpcVallige()
{
	INIT_TALK_IN_NPC(NpcVallige);
	m_name = "NpcVallige";
}

NpcVallige::~NpcVallige()
{

}

void NpcVallige::collisionEvent()
{
	Npc::collisionEvent();
}
