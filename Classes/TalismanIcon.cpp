#include"TalismanIcon.h"
#include"Path.h"
#include"ConfigUtils.h"

TalismanIcon * TalismanIcon::createWithName()
{
	TalismanIcon* pRet = new TalismanIcon("");
	if (pRet&&pRet->init())
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

bool TalismanIcon::init()
{
	if (Thing::init())
	{
		m_icon = cocos2d::ui::ImageView::create();
		this->addChild(m_icon);
		return true;
	}
	return false;
}

void TalismanIcon::updateUI(const std::string & name)
{
	m_name = name;
	m_icon->loadTexture(getTalismanPath(name));
	updateProperty();
}


float TalismanIcon::beUse(cocos2d::CCObject * obj, cocos2d::CCObject * who, cocos2d::CCObject * towho)
{
	return 0.0f;
}

TalismanIcon::TalismanIcon(const std::string& name)
	:Thing(std::string(""))
{

}

void TalismanIcon::updateProperty()
{
	auto attrmaps = ConfigUtils::getInstance()->getConfigAttr(getTalismanPurePath(m_name));
	m_textname = attrmaps["textname"];
}

TalismanIcon::~TalismanIcon()
{
}