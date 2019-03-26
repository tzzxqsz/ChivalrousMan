#include"SectActiveLayer.h"
#include"Commen.h"
#include"ui/UIButton.h"
#include"Path.h"
#include"GameData.h"
#include"UIHelper.h"
#include"ConfigUtils.h"

bool SectActiveLayer::init()
{
	if (Layer::init())
	{
		auto size = SCREEN;
		m_imageBg = cocos2d::ui::ImageView::create();
		this->addChild(m_imageBg);
		m_imageBg->setPosition(cocos2d::Vec2(size.width*0.5, size.height*0.5));

		auto m_xiulian = cocos2d::ui::Button::create(getCommonPath("Effect"));
		m_xiulian->setTitleFontSize(32);
		m_xiulian->setTitleFontName(getFontPath("font2"));
		m_xiulian->setTitleText(StringValue("XiulianText"));
		this->addChild(m_xiulian);

		auto gongfa = cocos2d::ui::Button::create(getCommonPath("Effect"));
		gongfa->setTitleFontSize(32);
		gongfa->setTitleFontName(getFontPath("font2"));
		gongfa->setTitleText(StringValue("GongfaText"));
		this->addChild(gongfa);

		m_nodeDec = cocos2d::Node::create();
		this->addChild(m_nodeDec);
		m_nodeDec->setPosition(20, size.height - 30);

		m_title = UIHelper::getInstance()->createTTFConfigLabel("", 45);
		m_title->setPosition(size.width*0.5, size.height - 40);
		this->addChild(m_title);
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

void SectActiveLayer::updateDec()
{
	auto desc = ConfigUtils::getInstance()->getConfigDec(getSectPath(m_name));
	m_title->setString(desc[CONFIG_NAME]);
}

void SectActiveLayer::updateAttrs()
{
	auto attrs = ConfigUtils::getInstance()->getConfigAttr(getSectPath(m_name));
	
}
