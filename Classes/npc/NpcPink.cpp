#include"NpcPink.h"
#include"tool/GameData.h"
#include"tool/GameDynamicData.h"
#include"GameScene.h"
#include"main/GameLogicLayer.h"
#include"main/DealLayer.h"
#include"tool/Commen.h"

DEF_REFLECT_FUNC(NpcPink)
 
NpcPink::NpcPink()
{
	INIT_TALK_IN_NPC(NpcPink);
	m_name = "NpcPink";
}

NpcPink::~NpcPink()
{

}

void NpcPink::collisionEvent()
{
	Npc::collisionEvent();
}

void NpcPink::endCollisionEvent()
{
	Npc::endCollisionEvent();
	CurGameScene()->removeChildByName("DealLayer");
}

void NpcPink::talkEndEvent()
{
	Npc::talkEndEvent();
	auto gs = CurGameScene();
	auto dealLayer = DealLayer::createWithType(MEDICATION, StringValue("DealMedication"));
	dealLayer->setName("DealLayer");
	gs->addChild(dealLayer);
}