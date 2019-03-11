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
		auto leftArrow = CommonButton::createCommonButton(getButtonPath("left_btn"));
		this->addChild(leftArrow);
		leftArrow->addClickCallback(CC_CALLBACK_1(TalismanLayer::onLeftClickCallback, this));
		leftArrow->setPosition(centerPos.x - visibleSize.width*0.5, centerPos.y);
		auto rightArrow = CommonButton::createCommonButton(getButtonPath("right_btn"));
		this->addChild(rightArrow);
		rightArrow->addClickCallback(CC_CALLBACK_1(TalismanLayer::onRightClickCallback, this));
		rightArrow->setPosition(centerPos.x + visibleSize.width*0.5, centerPos.y);

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

		m_desc = Node::create();
		m_desc->setPosition(centerPos.x - visibleSize.width*0.5 + 40, centerPos.y + visibleSize.height*0.5 - 90);
		this->addChild(m_desc);

		m_avatar = TalismanAvatar::create();
		this->addChild(m_avatar);
		m_avatar->setPosition(centerPos);

		auto pro = CommonProcessBar::create(getCommonPath("BarBG"), getCommonPath("bar"));
		this->addChild(pro);
		pro->setPosition(centerPos.x + 20, centerPos.y - visibleSize.height*0.5 + 120);
		pro->setValue(100);
		auto fragment = TalismanFragment::createWithName("ChaoticMirror");
		this->addChild(fragment);
		fragment->setPosition(centerPos.x - 185, centerPos.y - visibleSize.height*0.5 + 120);

		auto btn = CommonButton::createCommonButton(getButtonPath("CommonBtn"));
		this->addChild(btn);
		btn->setPosition(centerPos.x, centerPos.y - visibleSize.height*0.5 + 80);
		return true;
	}
	return false;
}

void TalismanLayer::onEnter()
{
	CommonTouchLayer::onEnter();
	updateView();
}

void TalismanLayer::updateView()
{
	m_avatar->updateAvatar("ChaoticMirror");
	updateDes();
}

void TalismanLayer::updateDes()
{
	auto screenSize = SCREEN;
	auto dec = ConfigUtils::getInstance()->getConfigDec(getTalismanPurePath("ChaoticMirror"));
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
		label->setPosition(0, -i * 36);
	}
}

void TalismanLayer::onLeftClickCallback(cocos2d::CCObject * sender)
{

}

void TalismanLayer::onRightClickCallback(cocos2d::CCObject * sender)
{
	
}
