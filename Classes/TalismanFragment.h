#pragma once
#ifndef __TALISMAN_FRAGMENT_H__
#define __TALISMAN_FRAGMENT_H__
#include"Thing.h"
#include"ui/UIImageView.h"

class TalismanFragment :public Thing
{
public:
	static TalismanFragment* createWithName(const std::string& name);

	virtual bool init() override;

	void updateUI(const std::string& name);
private:
	TalismanFragment(const std::string& name);
	virtual ~TalismanFragment();

	void onClick(cocos2d::CCObject* sender);

	void updateProperty(const std::string& pathname);
	
	cocos2d::ui::ImageView* m_fragment;
	std::string m_talismanName;
};

#endif // !__TalismanFragment_H__