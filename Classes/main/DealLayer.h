#pragma once
#ifndef __DEAL_LAYER_H__
#define __DEAL_LAYER_H__
#include"tool/PreProcess.h"
#include"common/CommonTouchLayer.h"
#include"base/Thing.h"
#include<vector>
#include<string>

/*
*class DealLayer
*交易层
*/
class DealLayer Inherit(CommonTouchLayer)
{
	CLASS_ESSENTAIL(DealLayer)
public:
	/*
	*根据触发类型创建一个物品交易层
	*@param type：指定触发类型
	*/
	static DealLayer* createWithType(const int& type,const std::string& name);

	bool init(const int& type, const std::string& name);
private:
	/*
	*checkBuy(float money);
	*检查是否可以购买
	*@param money：物品价格
	*/
	void checkBuy(float money);

	/*
	*购买按钮回调函数
	*/
	void onBuyBtnCallBack(cocos2d::CCObject* sender);
	
	/*
	*onCloseBtnCallBack(cocos2d::CCObject* sender);
	*关闭按钮回调函数
	*/
	void onCloseBtnCallBack(cocos2d::CCObject* sender);

	/*
	*初始化交易层的物品
	*/
	void initThingByName(const int& type,const std::string& name);

	/*
	*点击物品的回调函数
	*/
	void onClickThingCallBack(cocos2d::CCObject* sender);
	
	//交易类型
	int m_type;
	cocos2d::Vec2 m_basePoint;
	cocos2d::Sprite* m_selector;
	cocos2d::Menu* menu;
	cocos2d::CCObject* m_curSelect = nullptr;
};

#endif // !__DEAL_LAYER_H__
