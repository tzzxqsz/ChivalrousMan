#include"TalismanFragment.h"
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

		return true;
	}
	return false;
}