#pragma once
#ifndef __TALISMAN_H__
#define __TALISMAN_H__
#include"Thing.h"
#include"ui/UIImageView.h"

//·¨±¦icon
class TalismanIcon :public Thing
{
public:
	virtual ~TalismanIcon();

	static TalismanIcon* createWithName();

	virtual bool init() override;

	void updateUI(const std::string& name);

	virtual float beUse(cocos2d::CCObject* obj, cocos2d::CCObject* who = nullptr, cocos2d::CCObject* towho = nullptr) override;
private:
	TalismanIcon(const std::string& name);

	void updateProperty();
	
	cocos2d::ui::ImageView* m_icon;
	std::string m_textname;
};

#endif // !__TALISMAN_H__

