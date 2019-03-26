#pragma once
#ifndef __UI_HELPER_H__
#define __UI_HELPER_H__
#include"PreProcess.h"

class UIHelper :public cocos2d::CCObject
{
	GET_SINGLE_OBJECT(UIHelper);
public:
	cocos2d::Label* createTTFConfigLabel(const std::string& text, const int& fontSize = 26, cocos2d::Color3B color = cocos2d::Color3B(255, 255, 255), const std::string& font = "font2");
private:

	SINGLE_ATTRIBUTES(UIHelper);
};

#endif // !__UI_HELPER_H__

