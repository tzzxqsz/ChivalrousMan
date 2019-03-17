#include"TalismanFragment.h"
#include"GameData.h"
#include"Path.h"
#include"Commen.h"
#include"Colors.h"
#include"ui/UIButton.h"
#include"ConfigUtils.h"

TalismanFragment::TalismanFragment(const std::string& name)
	:Thing("")
{
}

TalismanFragment::~TalismanFragment()
{
}

void TalismanFragment::onClick(cocos2d::CCObject * sender)
{

}

void TalismanFragment::updateProperty(const std::string& pathname)
{
	auto attrs = ConfigUtils::getInstance()->getConfigAttr(pathname + "_f");
	m_talismanName = attrs["textname"];
	m_sellglod = std::stof(attrs["sellgold"]);
	m_synthesis = std::stoi(attrs["synthesis"]);
}

TalismanFragment * TalismanFragment::createWithName()
{
	TalismanFragment* pRet = new TalismanFragment("");
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

bool TalismanFragment::init()
{
	if (Thing::init())
	{
		m_fragment = ui::ImageView::create();
		this->addChild(m_fragment);
		m_fragment->setScale(0.55);

		TTFConfig ttfConfig;
		ttfConfig.fontFilePath = getFontPath("font2"); //±ØÐëÅäÖÃ
		ttfConfig.fontSize = 22;
		auto text = Label::createWithTTF(ttfConfig, StringValue("FragmentText"));
		text->setColor(FRAGMENT_COLOR);
		this->addChild(text);
		text->setPosition(-10, -10);
		
		return true;
	}
	return false;
}

void TalismanFragment::updateUI(const std::string & name, bool isSuffix)
{
	std::string buff = name;
	if (isSuffix)
	{
		buff.assign(name.begin(), name.begin() + name.size() - 2);
	}
	m_fragment->loadTexture(getTalismanPath(buff + "_icon"));
	updateProperty(getTalismanPurePath(buff));
}
