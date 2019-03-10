#pragma once
#ifndef __TALISMAN_H__
#define __TALISMAN_H__
#include"Thing.h"

//·¨±¦icon
class TalismanIcon :public Thing
{
public:
	virtual ~TalismanIcon();

	static TalismanIcon* createWithName(const std::string& name);

	virtual bool init() override;
private:
	TalismanIcon(const std::string& name);
	
	std::string m_talismanName;
};

#endif // !__TALISMAN_H__

