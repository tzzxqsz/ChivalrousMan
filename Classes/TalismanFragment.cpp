#include"TalismanFragment.h"
#include"GameData.h"
#include"Path.h"
#include"Commen.h"
#include"Colors.h"
#include<fstream>

TalismanFragment::TalismanFragment(const std::string& name)
	:Thing(std::string("talisman/") + name)
{
	initProperty();
}

TalismanFragment::~TalismanFragment()
{
}

void TalismanFragment::initProperty()
{
	std::string realname = m_name;
	realname += "_f.att";
	std::ifstream fin;
	fin.open(realname, std::ios::in);
	if (fin.fail())
	{
		return;
	}
	std::string tmp;
	fin >> tmp;
	ADD_PROPERTY(buyglod);
	ADD_PROPERTY(sellglod);
	fin.close();
}

TalismanFragment * TalismanFragment::createWithName(const std::string & name)
{
	TalismanFragment* pRet = new TalismanFragment(name);
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
		m_fragment->loadTexture(m_name + "_icon.png");
		this->addChild(m_fragment);
		m_fragment->setScale(0.6);

		TTFConfig ttfConfig;
		ttfConfig.fontFilePath = getFontPath("font2"); //±ØÐëÅäÖÃ
		ttfConfig.fontSize = 22;
		auto text = Label::createWithTTF(ttfConfig, StringValue("FragmentText"));
		text->setColor(PURPLE_COLOR);
		this->addChild(text);
		text->setPosition(-10, 10);
		return true;
	}
	return false;
}

void TalismanFragment::updateUI(const std::string & name)
{
	m_fragment->loadTexture(getTalismanPath(name + "_icon"));
}
