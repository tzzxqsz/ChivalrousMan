#include"TalismanIcon.h"
#include"Path.h"
#include"ConfigUtils.h"
#include"UIHelper.h"

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
		m_icon->setScale(0.55);
		this->addChild(m_icon);
		return true;
	}
	return false;
}

void TalismanIcon::updateUI(const std::string & name)
{
	m_name = name;
	m_icon->loadTexture(getTalismanPath(name + std::string("_icon")));
	updateProperty();
}


float TalismanIcon::beUse(cocos2d::CCObject * obj, cocos2d::CCObject * who, cocos2d::CCObject * towho)
{
	auto name = UIHelper::getInstance()->createTTFConfigLabel(m_textname, 200);
	dynamic_cast<cocos2d::Node*>(obj)->addChild(name);
	name->setScale(0.1);
	auto size = cocos2d::Director::getInstance()->getWinSize();
	name->setPosition(size.width*0.5, size.height*0.5);
	auto fade = cocos2d::FadeOut::create(1.5);
	auto scale = cocos2d::ScaleTo::create(2, 1);
	auto out = cocos2d::Spawn::createWithTwoActions(fade, scale);
	auto remove = cocos2d::RemoveSelf::create(true);
	auto squence = cocos2d::Sequence::createWithTwoActions(out, remove);
	name->runAction(squence);
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