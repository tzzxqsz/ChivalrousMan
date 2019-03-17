#include"TalismanLayer.h"
#include"CommonButton.h"
#include"Commen.h"
#include"Path.h"
#include"Colors.h"
#include"GameData.h"
#include"TalismanAvatar.h"
#include"ConfigUtils.h"
#include"CommonProcessBar.h"
#include"CommonButton.h"
#include"TalismanFragment.h"
#include"TalismanManager.h"
#include"BackPackManager.h"

bool TalismanLayer::init()
{
	if (CommonTouchLayer::init())
	{
		auto screenSize = SCREEN;
		auto centerPos = Vec2(screenSize.width*0.5, screenSize.height*0.5);
		auto bg = Sprite::create(getBackgroundPath("StyleBg4"));
		bg->setPosition(centerPos);
		auto visibleSize = bg->getContentSize();
		setExcludeRect(bg->getPosition(), bg->getTextureRect());
		this->addChild(bg);
		m_leftArrow = CommonButton::createCommonButton(getButtonPath("left_btn"));
		this->addChild(m_leftArrow);
		m_leftArrow->addClickCallback(CC_CALLBACK_1(TalismanLayer::onLeftClickCallback, this));
		m_leftArrow->setPosition(centerPos.x - visibleSize.width*0.5, centerPos.y);
		m_rightArrow = CommonButton::createCommonButton(getButtonPath("right_btn"));
		this->addChild(m_rightArrow);
		m_rightArrow->addClickCallback(CC_CALLBACK_1(TalismanLayer::onRightClickCallback, this));
		m_rightArrow->setPosition(centerPos.x + visibleSize.width*0.5, centerPos.y);

		TTFConfig ttfConfig;
		ttfConfig.fontFilePath = getFontPath("font2"); //±ØÐëÅäÖÃ
		ttfConfig.fontSize = 32;
		m_tilasmanName = Label::createWithTTF(ttfConfig,"");
		this->addChild(m_tilasmanName);
		m_tilasmanName->setColor(TITLE_COLOR);
		m_tilasmanName->setPosition(centerPos.x, centerPos.y + visibleSize.height*0.5 - 50);
		
		m_tilsmanGrade = Label::createWithTTF(ttfConfig, "+100");
		this->addChild(m_tilsmanGrade);
		m_tilsmanGrade->setColor(TWO_TITLE_COLOR);
		m_tilsmanGrade->setPosition(centerPos.x, centerPos.y + visibleSize.height*0.5 - 84);

		m_avatar = TalismanAvatar::create();
		this->addChild(m_avatar);
		m_avatar->setPosition(centerPos);

		m_progress = CommonProcessBar::create(getCommonPath("BarBG"), getCommonPath("bar"));
		this->addChild(m_progress);
		m_progress->setPosition(centerPos.x + 20, centerPos.y - visibleSize.height*0.5 + 120);
		m_progress->visibleValue(true);
		m_fragment = TalismanFragment::createWithName();
		this->addChild(m_fragment);
		m_fragment->setPosition(centerPos.x - 185, centerPos.y - visibleSize.height*0.5 + 120);

		m_synthesisBtn = CommonButton::createCommonButton(getButtonPath("CommonBtn"));
		this->addChild(m_synthesisBtn);
		m_synthesisBtn->setFontSize(32);
		m_synthesisBtn->addClickCallback(CC_CALLBACK_1(TalismanLayer::onSynthesisClickCallback, this));
		m_synthesisBtn->setPosition(centerPos.x, centerPos.y - visibleSize.height*0.5 + 80);

		m_battleBtn = CommonButton::createCommonButton(getButtonPath("v_btn"));
		this->addChild(m_battleBtn);
		m_battleBtn->addClickCallback(CC_CALLBACK_1(TalismanLayer::onBattleClickCallback, this));
		m_battleBtn->setPosition(centerPos.x + visibleSize.width*0.5 - 90, centerPos.y + visibleSize.height*0.5 - 130);
		
		m_desc = Node::create();
		m_desc->setCascadeOpacityEnabled(true);
		m_desc->setOpacity(190);
		m_desc->setPosition(centerPos.x - visibleSize.width*0.5 + 40, centerPos.y + visibleSize.height*0.5 - 90);
		this->addChild(m_desc);
		return true;
	}
	return false;
}

void TalismanLayer::onEnter()
{
	CommonTouchLayer::onEnter();
	TalismanManager::getInstance()->mergeTalismanInfo();
	m_curIndex = 0;
	updateArrow();
}

void TalismanLayer::updateView()
{
	auto info = TalismanManager::getInstance()->getTalismanInfo(m_curIndex);
	m_avatar->updateAvatar(info.name);
	updateDes(info.name);
	updateButton(info.isInBattle == 1);
	m_synthesisBtn->setString(info.have ? StringValue("UpText") : StringValue("MergeText"));
	m_tilsmanGrade->setString("+" + NTS(info.grade));
	m_fragment->updateUI(info.name);
	m_progress->setMax(float(m_fragment->getSynthesis()));
	int nums = BackPackManager::getInstance()->ThingNums(info.name + "_f");
	m_progress->setValue(nums);
}

void TalismanLayer::updateDes(const std::string& name)
{
	auto screenSize = SCREEN;
	auto dec = ConfigUtils::getInstance()->getConfigDec(getTalismanPurePath(name));
	m_tilasmanName->setString(dec[CONFIG_NAME]);
	int size = dec.size();
	TTFConfig ttfConfig;
	ttfConfig.fontFilePath = getFontPath("font2"); //±ØÐëÅäÖÃ
	ttfConfig.fontSize = 32;
	m_desc->removeAllChildren();
	for (int i = CONFIG_NAME + 1; i < size; ++i)
	{
		auto label = Label::createWithTTF(ttfConfig, dec[i]);
		label->setAnchorPoint(Vec2(0, 0.5));
		m_desc->addChild(label);
		label->setColor(DEC_COLOR);
		label->setCascadeOpacityEnabled(true);
		label->setPosition(0, -i * 36);
	}
}

void TalismanLayer::onLeftClickCallback(cocos2d::CCObject * sender)
{
	m_curIndex--;
	updateArrow();
}

void TalismanLayer::onRightClickCallback(cocos2d::CCObject * sender)
{
	m_curIndex++;
	updateArrow();
}

void TalismanLayer::onBattleClickCallback(cocos2d::CCObject * sender)
{
}

void TalismanLayer::onSynthesisClickCallback(cocos2d::CCObject * sender)
{
}

void TalismanLayer::updateArrow()
{
	int size = TalismanManager::getInstance()->getTalismanSize();
	m_leftArrow->setVisible(m_curIndex > 0);
	m_rightArrow->setVisible(m_curIndex < size - 1);
	if (m_curIndex <= 0)
	{
		m_curIndex = 0;
	}
	if (m_curIndex >= size - 1)
	{
		m_curIndex = size - 1;
	}
	updateView();
}

void TalismanLayer::updateButton(const bool& isInBattle)
{
	if (isInBattle)
	{
		m_battleBtn->setButtonImage(getButtonPath("v_btn1"));
	}
	else
	{
		m_battleBtn->setButtonImage(getButtonPath("v_btn"));
	}
}
