#pragma once
#ifndef __MAX_TOP_LAYER_H__
#define __MAX_TOP_LAYER_H__
#include"PreProcess.h"
#include<vector>
#include"jsonCpp/value.h"

class Slot;

class MaxTopLayer :public cocos2d::Node
{
	CLASS_ESSENTAIL(MaxTopLayer);
public:
	static void attach();

	virtual void onEnter() override;

	virtual void onExit() override;

	void popupTips(Json::Value& msg);
private:
	
	std::vector<Slot*> m_slots;
};

#endif // !__MAX_TOP_LAYER_H__
