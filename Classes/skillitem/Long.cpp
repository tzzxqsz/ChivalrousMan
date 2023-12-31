#include"Long.h"
#include"tool/Commen.h"
#include"fight/FightLayer.h"
#include"base/Monster.h"

bool Long::init(Layer* parent,cocos2d::CCObject* towho, const float& baseattack)
{
	if (RealSkill::init())
	{
		m_parent = parent;
		m_baseattack = baseattack;
		m_towho = towho;
		Vec2 pos = ((Monster*)m_towho)->getPosition();
		this->setPosition(pos.x+30, pos.y);
		m_parent->addChild(this);

		//LoadAnimationFromMinFile(, 10, 0.15, animation);
		Animate* animate = Animate::create(getAnimation("Skill/Long/Long"));
		this->runAction(animate);

		scheduleOnce(schedule_selector(Long::died), 1.5);
		scheduleOnce(schedule_selector(Long::heart), 0.9);
		this->setTag(1.5);    //使用tag标记技能持续时间
		return true;
	}
	return false;
}

void Long::heart(float dt)
{
	dynamic_cast<Monster*>(m_towho)->beAttack(m_baseattack);
}