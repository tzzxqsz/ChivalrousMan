#pragma once
#ifndef __SECT_MANAGER_H__
#define __SECT_MANAGER_H__
#include"PreProcess.h"

class SectManager :public cocos2d::CCObject
{
	GET_SINGLE_OBJECT(SectManager);
public:
	void joinSect(const std::string& name);


private:
	SINGLE_ATTRIBUTES(SectManager);
};

#endif // !__SECT_MANAGER_H__

