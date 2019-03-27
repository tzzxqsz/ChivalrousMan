#include"SectActiveLayer.h"
#include"Commen.h"
#include"Path.h"
#include"GameData.h"
#include"UIHelper.h"
#include"ConfigUtils.h"

bool SectActiveLayer::init()
{
	if (CommonTouchLayer::init())
	{
		auto size = SCREEN;
		m_imageBg = cocos2d::ui::ImageView::create();
		this->addChild(m_imageBg);
		m_imageBg->setPosition(cocos2d::Vec2(size.width*0.5, size.height*0.5));
		setExcludeRect(m_imageBg->getPosition(), cocos2d::Rect(0, 0, size.width, size.height));

		m_xiulian = cocos2d::ui::Button::create(getCommonPath("Effect"));
		m_xiulian->setTitleFontSize(32);
		m_xiulian->setTitleFontName(getFontPath("font2"));
		m_xiulian->setTitleText(StringValue("XiulianText"));
		this->addChild(m_xiulian);

		m_gongfa = cocos2d::ui::Button::create(getCommonPath("Effect"));
		m_gongfa->setTitleFontSize(32);
		m_gongfa->setTitleFontName(getFontPath("font2"));
		m_gongfa->setTitleText(StringValue("GongfaText"));
		this->addChild(m_gongfa);

		m_nodeDec = cocos2d::Node::create();
		this->addChild(m_nodeDec);
		m_nodeDec->setPosition(20, size.height - 30);

		m_title = UIHelper::getInstance()->createTTFConfigLabel("", 45);
		m_title->setPosition(size.width*0.5, size.height - 40);
		this->addChild(m_title);

		auto backBtn = ui::Button::create(getButtonPath("back_btn"));
		this->addChild(backBtn);
		backBtn->setPosition(Vec2(backBtn->getContentSize().width*0.5 + 5, size.height - 34));
		backBtn->addClickEventListener(CC_CALLBACK_1(SectActiveLayer::onBackClickCallback, this));
		return true;
	}
	return false;
}

void SectActiveLayer::updateUI(const std::string & name)
{
	m_name = name;
	m_imageBg->loadTexture(getSectBgPath(name));
	updateDec();
	updateAttrs();
}

void SectActiveLayer::onBackClickCallback(cocos2d::CCObject * sender)
{
	removeFromParent();
}

void SectActiveLayer::onXiulianClickCallback(cocos2d::CCObject * sender)
{
}

void SectActiveLayer::onGongfaClickCallback(cocos2d::CCObject * sender)
{
}

void SectActiveLayer::updateDec()
{
	auto desc = ConfigUtils::getInstance()->getConfigDec(getSectPath(m_name));
	m_title->setString(desc[CONFIG_NAME]);
}

void SectActiveLayer::updateAttrs()
{
	auto attrs = ConfigUtils::getInstance()->getConfigAttr(getSectPath(m_name));
	cocos2d::Vec2 pos;
	pos.x = std::stof(attrs["xiulianX"]);
	pos.y = std::stof(attrs["xiulianY"]);
	m_xiulian->setPosition(pos);
	pos.x = std::stof(attrs["gongfaX"]);
	pos.y = std::stof(attrs["gongfaY"]);
	m_gongfa->setPosition(pos);
}
