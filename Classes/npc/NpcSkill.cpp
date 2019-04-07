#include"NpcSkill.h"
#include"tool/GameData.h"
#include"tool/GameDynamicData.h"
#include"GameScene.h"
#include"main/GameLogicLayer.h"
#include"main/DealLayer.h"
#include"tool/Commen.h"

DEF_REFLECT_FUNC(NpcSkill)

NpcSkill::NpcSkill()
{
	INIT_TALK_IN_NPC(NpcSkill);
	m_name = "NpcSkill";
} 

NpcSkill::~NpcSkill()
{

}

void NpcSkill::collisionEvent()
{
	Npc::collisionEvent();
}

void NpcSkill::talkEndEvent()
{
	Npc::talkEndEvent();
	auto gs = CurGameScene();
	auto dealLayer = DealLayer::createWithType(SKILL, StringValue("DealSkill"));
	gs->addChild(dealLayer);
}
