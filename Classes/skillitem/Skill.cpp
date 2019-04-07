#include"Skill.h"
#include"tool/Commen.h"
#include"fight/FightLayer.h"
#include"tool/SkillFactory.h"
#include"player/CameraPlayer.h"
#include"common/TipLayer.h"
#include"tool/GameData.h"
#include"ui/UIImageView.h"
#include<fstream>

Skill::Skill(const std::string& name):
	Thing(name)
{
	initProperty(name);
	m_grade = 1;
}

Skill::~Skill()
{

}

Skill* Skill::createWithImage(const std::string& filename)
{
	Skill* pRet = new Skill(getfileName(filename));
	if (pRet&&pRet->init(filename))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool Skill::init(const std::string& filename)
{
	if (Thing::init())
	{
		auto face = ui::ImageView::create(filename);
		this->addChild(face);

		return true;
	}
	return false;
}

void Skill::initProperty(const std::string& name)
{
	std::string realname = name;
	realname += ".att";
	std::fstream fin;
	fin.open(realname, std::ios::in);
	if (fin.fail())
	{
		return;
	}
	std::string tmp;
	fin >> m_name;
	fin >> m_name;
	fin >> m_name;
	ADD_PROPERTY(buyglod);
	ADD_PROPERTY(sellglod);
	ADD_PROPERTY(baseAttack);
	ADD_PROPERTY(baseMana);
	ADD_PROPERTY(baseupGlod);
	fin.close();
}

float Skill::beUse(cocos2d::CCObject* obj,cocos2d::CCObject* who,cocos2d::CCObject* towho)
{
	FightLayer* pFt = dynamic_cast<FightLayer*>(obj);
	RealSkill* skill = SkillFactory::createSkill(m_name, pFt, towho, m_baseAttack + 30 * m_grade);
	auto move1 = MoveBy::create(0.2, ccp(-20, 0));
	auto move2 = MoveBy::create(0.2, ccp(20, 0));
	((Node*)who)->runAction(Sequence::createWithTwoActions(move1, move2));
	return skill->getTag();
}

void Skill::incGrade()
{
	++m_grade;
}

float Skill::getUseMana()
{
	return m_baseMana + m_grade * 10;
}