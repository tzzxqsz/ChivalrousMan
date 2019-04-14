#pragma once
#ifndef __BUFF_H__
#define __BUFF_H__
#include<2d/CCNode.h>
#include<2d/CCSprite.h>
#include<string>
#include<unordered_map>

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

	cocos2d::Sprite* m_buffFaces;
	int m_times;
	std::unordered_map<std::string, int> m_buffAttr;
};

#endif // !__BUFF_H__

