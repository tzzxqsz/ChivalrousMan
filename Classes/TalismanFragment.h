#pragma once
#ifndef __TALISMAN_FRAGMENT_H__
#define __TALISMAN_FRAGMENT_H__
#include"Thing.h"

class TalismanFragment :public Thing
{
public:
	static TalismanFragment* createWithName(const std::string& name);

	virtual bool init() override;
private:
	TalismanFragment(const std::string& name);
	virtual ~TalismanFragment();
	void initProperty();
	
	std::string m_talismanName;
};

#endif // !__TalismanFragment_H__