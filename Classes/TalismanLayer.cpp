#include"TalismanLayer.h"
#include"CommonButton.h"
#include"Commen.h"
#include"Path.h"
#include"Colors.h"
#include"GameData.h"

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
		m_tilasmanName = Label::createWithTTF(ttfConfig, StringValue("OffLine"));
		this->addChild(m_tilasmanName);
		m_tilasmanName->setColor(TITLE_COLOR);
		m_tilasmanName->setPosition(centerPos.x, centerPos.y + visibleSize.height*0.5 - 50);
		
		m_tilsmanGrade = Label::createWithTTF(ttfConfig, "+100");
		this->addChild(m_tilsmanGrade);
		m_tilsmanGrade->setColor(TWO_TITLE_COLOR);
		m_tilsmanGrade->setPosition(centerPos.x, centerPos.y + visibleSize.height*0.5 - 90);

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

}

void TalismanLayer::onLeftClickCallback(cocos2d::CCObject * sender)
{

}

void TalismanLayer::onRightClickCallback(cocos2d::CCObject * sender)
{
	
}
