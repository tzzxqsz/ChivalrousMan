#include"CommonProcessBar.h"
#include"tool/Commen.h"
#include"tool/GameData.h"

CommonProcessBar* CommonProcessBar::create(const std::string& bgfile, const std::string& barfile)
{
	CommonProcessBar* pRet = new CommonProcessBar;
	if (pRet&&pRet->init(bgfile, barfile))
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

bool CommonProcessBar::init(const std::string & bgfile, const std::string & barfile)
{
	if (Node::init())
	{
		m_bg = Sprite::create(bgfile);
		this->addChild(m_bg);
		m_bar = Sprite::create(barfile);
		auto size = m_bg->getContentSize();
		auto m_initSize = m_bar->getContentSize();
		m_progress = ProgressTimer::create(m_bar);
		m_progress->setType(ProgressTimer::Type::BAR);
		m_progress->setMidpoint(ccp(0, 0));
		m_progress->setBarChangeRate(ccp(1, 0));
		m_progress->setPercentage(0);
		this->addChild(m_progress);

		m_value = LabelTTF::create();
		this->addChild(m_value);
		m_value->setVisible(false);
		return true;
	}
	return false;
}

void CommonProcessBar::setValue(const float& value)
{
	m_progress->setPercentage(value / m_max * 100);
	m_value->setString(NTS(value) + "/" + NTS(m_max));
}

void CommonProcessBar::setMax(const float & max)
{
	m_max = max;
}

void CommonProcessBar::visibleValue(const bool & b)
{
	m_value->setVisible(b);
}
