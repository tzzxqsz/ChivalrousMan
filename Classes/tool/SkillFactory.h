#pragma once
#ifndef __SKILL_FACTORY_H__
#define __SKILL_FACTORY_H__
#include"PreProcess.h"
#include"skillitem/RealSkill.h"
#include<string>

class SkillFactory
{
	CLASS_ESSENTAIL(SkillFactory)
public:
	static RealSkill* createSkill(std::string name, cocos2d::Layer* parent,cocos2d::CCObject* towho, const float& attack);
};

#endif // !__SKILL_FACTORY_H__

