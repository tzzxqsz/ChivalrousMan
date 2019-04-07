#include"NpcEquip.h"
#include"tool/GameData.h"
#include"main/DealLayer.h"
#include"tool/GameDynamicData.h"
#include"GameScene.h"
#include"main/GameLogicLayer.h"
#include"tool/Commen.h"

DEF_REFLECT_FUNC(NpcEquip)

NpcEquip::NpcEquip()
{
	INIT_TALK_IN_NPC(NpcEquip);
	m_name = "NpcEquip";
}
  
NpcEquip::~NpcEquip()
{

}

void NpcEquip::collisionEvent()
{
	Npc::collisionEvent();
}

void NpcEquip::talkEndEvent()
{
	Npc::talkEndEvent();
	auto gs = CurGameScene();
	auto dealLayer = DealLayer::createWithType(EQUIPMENT, StringValue("DealEquipMent"));
	gs->addChild(dealLayer);
}