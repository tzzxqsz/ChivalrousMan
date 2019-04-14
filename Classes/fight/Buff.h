#pragma once
#ifndef __BUFF_H__
#define __BUFF_H__
#include"2d/CCNode.h"
#include<string>

class Buff :public cocos2d::Node
{
public:
	virtual ~Buff();

	virtual void attachTo(cocos2d::Node* node);

	virtual void setTimes(const int& times);

	virtual void play();

	virtual bool init();

	virtual void decTimes();
protected:
	virtual void decodeAttr(const std::string& name);

	int times;
};

#endif // !__BUFF_H__

