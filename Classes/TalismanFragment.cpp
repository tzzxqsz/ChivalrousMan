#include"TalismanFragment.h"
#include"GameData.h"
#include"Path.h"
#include"Commen.h"
#include"Colors.h"
#include"ui/UIButton.h"
#include"ConfigUtils.h"
#include"BackPackManager.h"

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
	m_buyglod = std::stof(attrs["sellgold"]);
	m_sellglod = std::stof(attrs["sellgold"]);
	m_synthesis = std::stoi(attrs["synthesis"]);
}

void TalismanFragment::updateDetail(const std::string & pathname)
{
	auto details = ConfigUtils::getInstance()->getConfigDec(pathname + "_f");
	m_details.clear();
	m_details = details;
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
		
	    m_nums = LabelTTF::create("", "¿¬Ìå", 20);
		m_nums->setPosition(-18, -14);
		m_nums->setColor(ccc3(255, 242, 0));
		this->addChild(m_nums);
		m_nums->setVisible(false);
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
	m_id = buff + std::string("_f");
	m_name = m_id;
	m_fragment->loadTexture(getTalismanPath(buff + "_icon"));
	updateProperty(getTalismanPurePath(buff));
	updateDetail(getTalismanPurePath(buff));
}

std::string TalismanFragment::getId()
{
	return m_id;
}

std::string TalismanFragment::getFragmentName()
{
	return m_talismanName;
}

void TalismanFragment::setVisibleNums(bool visible)
{
	m_nums->setVisible(visible);
	if (visible)
	{
		int nums = BackPackManager::getInstance()->ThingNums(m_id);
		m_nums->setString(NTS(nums));
	}
}
