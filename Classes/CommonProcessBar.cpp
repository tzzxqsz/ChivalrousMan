#include"CommonProcessBar.h"

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
	return false;
}
