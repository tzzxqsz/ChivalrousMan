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
private:

};

#endif // !__COMMON_PROCESS_H__

