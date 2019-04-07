#include"SectRukou.h"
#include"tool/ConfigUtils.h"
#include"tool/Path.h"
#include"tool/GameData.h"
#include"ui/UIButton.h"

bool SectRukou::init()
{
	if (Node::init())
	{
		m_image = cocos2d::ui::ImageView::create();
		this->addChild(m_image);

		cocos2d::TTFConfig ttfConfig;
		ttfConfig.fontFilePath = getFontPath("font2"); //±ØÐëÅäÖÃ
		ttfConfig.fontSize = 30;
		m_textname = cocos2d::Label::createWithTTF(ttfConfig, "");
		this->addChild(m_textname);
		m_textname->setPosition(0, 180);

		auto joinBtn = cocos2d::ui::Button::create(getButtonPath("CommonBtn"));
		joinBtn->setTitleFontName(getFontPath("font2"));
		joinBtn->setTitleFontSize(28);
		joinBtn->setTitleText(StringValue("JoinText"));
		joinBtn->addClickEventListener(CC_CALLBACK_1(SectRukou::onJoinClickCallback, this));
		joinBtn->setPosition(cocos2d::Vec2(0, -200));
		this->addChild(joinBtn);
		return true;
	}
	return false;
}

void SectRukou::updateUI(const std::string & name)
{
	m_image->loadTexture(getSectUIPath(name));
	setName(name);
	updateDec(name);
}

void SectRukou::addJoinClickCallback(cocos2d::ui::Widget::ccWidgetClickCallback callback)
{
	m_callback = callback;
}

cocos2d::Size SectRukou::getRokouSize()
{
	return m_image->getContentSize();
}

void SectRukou::onJoinClickCallback(cocos2d::CCObject * sender)
{
	if (m_callback)
		m_callback(this);
}

void SectRukou::updateDec(const std::string & name)
{
	auto decs = ConfigUtils::getInstance()->getConfigDec(getSectPath(name));
	m_textname->setString(decs[CONFIG_NAME]);
}
