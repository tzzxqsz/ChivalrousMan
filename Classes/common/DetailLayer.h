#pragma once
#ifndef  __DETAIL_LAYER_H__
#define __DETAIL_LAYER_H__
#include"tool/PreProcess.h"
#include"base/Thing.h"

class DetailLayer Inherit(cocos2d::Layer)
{
	CLASS_ESSENTAIL(DetailLayer)
public:
	static DetailLayer* createWithThing(const std::vector<std::string>& details, const int& costValue = -1);

	bool init(const std::vector<std::string>& details, const int& costValue);
private:
	/*
	*关闭按钮点击事件
	*/
	void onCloseClickCallBack(cocos2d::CCObject* sender);
};

#endif
