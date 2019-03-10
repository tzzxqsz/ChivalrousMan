#include"TalismanIcon.h"

TalismanIcon::TalismanIcon(const std::string& name)
	:Thing(std::string("talisman/")+name)
{
	m_talismanName = name;
}

TalismanIcon::~TalismanIcon()
{
}

TalismanIcon * TalismanIcon::createWithName(const std::string & name)
{
	TalismanIcon* pRet = new TalismanIcon(name);
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
		
		return true;
	}
	return false;
}
