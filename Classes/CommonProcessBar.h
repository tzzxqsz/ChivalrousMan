#pragma once
#ifndef __COMMON_PROCESS_H__
#define __COMMON_PROCESS_H__
#include"PreProcess.h"

class CommonProcessBar :public cocos2d::Node
{
	CLASS_ESSENTAIL(CommonProcessBar)
public:
	static CommonProcessBar* create(const std::string& bgfile, const std::string& barfile);

	bool init(const std::string& bgfile, const std::string& barfile);

	void setValue(const float& value);

private:
	cocos2d::Size m_initSize;
	cocos2d::Sprite* m_bg;
	cocos2d::Sprite* m_bar;
	cocos2d::ProgressTimer* m_progress;
};

#endif // !__COMMON_PROCESS_H__

