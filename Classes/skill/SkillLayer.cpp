#include"SkillLayer.h"
#include"tool/GameData.h"
#include"SkillManager.h"
#include"player/CameraPlayer.h"
#include"tool/Commen.h"
#include"skillitem/Skill.h"
#include"common/TipLayer.h"
#include<string>

bool SkillLayer::init()
{
	if (CommonTouchLayer::init())
	{
		auto size = SCREEN;
		auto back = Sprite::create(StringValue("SkillBg"));
		back->setPosition(size.width*0.5, size.height*0.5);
		this->addChild(back);
		setExcludeRect(back->getPosition(), back->getTextureRect());
		m_basePos = back->getPosition();
		m_basePos.y += 47;
		m_basePos.x = m_basePos.x - back->getContentSize().width*0.5 + 103;

		auto title = LabelTTF::create(StringValue("SkillText"), "楷体", 35);
		title->setColor(ccc3(63, 72, 204));
		title->setPosition(size.width*0.5, size.height*0.5 + 120);
		this->addChild(title);

		auto backGrid = Sprite::create(StringValue("SkillGrid"));
		backGrid->setPosition(size.width*0.5, size.height*0.5 + 50);
		this->addChild(backGrid);
		
		m_menu = Menu::create();
		m_menu->setPosition(0, 0);
		this->addChild(m_menu);

		//升级按钮
		auto btnUp = MenuItemImage::create(StringValue("BtnUp"),
			StringValue("BtnUp"), this, menu_selector(SkillLayer::onBtnUpClickCallback));
		btnUp->setPosition(size.width*0.5+230,size.height*0.5-140);
		m_menu->addChild(btnUp);
		
		initSkillIcon();

		m_selector = Sprite::create(StringValue("Selector"));
		m_selector->setContentSize(Size{ 40,40 });
		m_selector->setPosition(m_basePos.x-6, m_basePos.y - 3);
		this->addChild(m_selector);

		return true;
	}
	return false;
}

void SkillLayer::onBtnUpClickCallback(cocos2d::CCObject* sender)
{
	ClickAction();
	if (m_selectedSkill == nullptr)
	{
		TipLayer* tiplayer = TipLayer::createTipLayer(StringValue("NoSelectSkill"));
		this->addChild(tiplayer);
	}
	else
	{
		float glod = dynamic_cast<Skill*>(m_selectedSkill)->getbaseupGlod();
		glod += dynamic_cast<Skill*>(m_selectedSkill)->getgrade() * 50;
		if (glod >GetPlayerData().getglod())
		{
			TipLayer* tplayer = TipLayer::createTipLayer(StringValue("LackGlod"));
			this->addChild(tplayer);
			return;
		}
		GetPlayerData().subGlod(glod);
		dynamic_cast<Skill*>(m_selectedSkill)->incGrade();
		SkillManager::getInstance()->upSkill(dynamic_cast<Skill*>(m_selectedSkill)->getname());
		int index = dynamic_cast<Skill*>(m_selectedSkill)->getTag();
		int grade =  std::stoi(m_gradelabels[index]->getString());
		m_gradelabels[index]->setString("+"+NumberToString(grade + 1));
		m_upskillGlods[index]->setString(NumberToString(glod + 50));
	}
}

void SkillLayer::initSkillIcon()
{
	int index = 0;
	for (auto var : SkillManager::getInstance()->getSkillMap())
	{
		std::string filename = StringValue(var.first);
		filename += var.first;
		filename += ".png";
		auto skillicon = Skill::createWithImage(filename);
		skillicon->addClickCallback(CC_CALLBACK_1(SkillLayer::onSkillCkickCallBack, this));
		Vec2 pos = m_basePos;
		pos.x = pos.x + index * (56);
		pos.y += 3;
		skillicon->setPosition(pos);
		skillicon->setgrade(var.second);
		this->addChild(skillicon);
		auto gradelabel = LabelTTF::create("+" + NumberToString(var.second), "楷体", 20);
		gradelabel->setPosition(pos.x, pos.y - 37);
		gradelabel->setColor(ccc3(255, 128, 0));
		m_gradelabels.push_back(gradelabel);
		auto upglodLabel = LabelTTF::create(NumberToString(skillicon->getbaseupGlod() + var.second * 50), "楷体", 20);
		upglodLabel->setPosition(pos.x, pos.y - 60);
		upglodLabel->setColor(Color3B::RED);
		this->addChild(upglodLabel);
		m_upskillGlods.push_back(upglodLabel);
		skillicon->setTag(index);         //使用tag存放索引
		this->addChild(gradelabel);
		if (!index)
			m_selectedSkill = skillicon;
		++index;
	}
	if (!index)
		m_selectedSkill = nullptr;
}

void SkillLayer::onSkillCkickCallBack(cocos2d::CCObject* sender)
{
	Vec2 dest = dynamic_cast<Skill*>(sender)->getPosition();
	dest.x -= 8;
	dest.y -= 3;
	auto move = MoveTo::create(0.3, dest);
	m_selector->runAction(move);
	dynamic_cast<Skill*>(sender)->showDetail(this);
	m_selectedSkill = sender;
}