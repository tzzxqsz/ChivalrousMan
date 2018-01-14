#pragma once
#ifndef  __SKILL_H__
#define  __SKILL_H__
#include"Thing.h"

/*
*class Skill
*����ͼ��
*/
class Skill Inherit(Thing)
{
public:
	static Skill* createWithImage(const std::string& filename);
	
	bool init(const std::string& filename);

	Skill(const std::string& name);
	virtual ~Skill();
private: 
	void initProperty(const std::string& name);
	
	PROPERTY__REF(std::string, m_name, name)
	PROPERTY__REF(int,m_grade,grade)
};

#endif // ! __SKILL_H__