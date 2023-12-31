#include"Danate.h"
#include"fight/FightLayer.h"
#include"player/CameraPlayer.h"
#include"tool/GameData.h"
#include"base/Monster.h"
#include"tool/Commen.h"

Dante::Dante()
{

}

Dante::~Dante()
{
	
}


bool Dante::init(cocos2d::Layer* parent,cocos2d::CCObject* towho, const float& baseattack)
{
	if (RealSkill::init())
	{
		m_parent = parent;
		m_baseattack = baseattack;
		m_towho = towho;
		Vec2 pos = ((Monster*)m_towho)->getPosition();
		setPosition(pos.x+10, pos.y);
		m_parent->addChild(this);
		
		Animate* animate = Animate::create(getAnimation("Skill/Dante/Dante"));
		this->runAction(animate);

		scheduleOnce(schedule_selector(Dante::died), 2.6);
		scheduleOnce(schedule_selector(Dante::heart), 1.3);
		setTag(2.6);   //使用tag标记技能持续时间
		return true;
	}
	return false;
}

void Dante::heart(float dt)
{
	dynamic_cast<Monster*>(m_towho)->beAttack(m_baseattack);
}