#include"SkillFactory.h"
#include"Commen.h"
#include"skillitem/CrackIt.h"
#include"skillitem/Danate.h"
#include"skillitem/DragonRoar.h"
#include"skillitem/LightStrike.h"
#include"skillitem/Long.h"
#include"skillitem/RecallCountermand.h"
#include"skillitem/SealOfTheBlade.h"
#include"skillitem/XBArrow.h"

RealSkill* SkillFactory::createSkill(std::string name, cocos2d::Layer* parent,cocos2d::CCObject* towho, const float& attack)
{
	if (name == "CrackIt")
	{
		return CrackIt::create(parent,towho, attack);
	}
	else if (name=="Dante")
	{
		return Dante::create(parent, towho, attack);
	}
	else if (name == "DragonRoar")
	{
		return DragonRoar::create(parent, towho, attack);
	}
	else if (name == "LightStrike")
	{
		return  LightStrike::create(parent, towho, attack);
	}
	else if (name == "Long")
	{
		return Long::create(parent, towho, attack);
	}
	else if (name == "RecallCountermand")
	{
		return RecallCounterMand::create(parent, towho, attack);
	}
	else if (name == "SealOfTheBlade")
	{
		return SealOfTheBlade::create(parent, towho, attack);
	}
	else if (name == "XBArrow")
	{
		return XBArrow::create(parent, towho, attack);
	}
	else
	{
		return nullptr;
	}
}