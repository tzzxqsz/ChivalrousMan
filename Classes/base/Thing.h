#pragma once
#ifndef __THING_H__
#define __THING_H__
#include"tool/PreProcess.h"
#include"ui/UIButton.h"
#include<vector>
#include<string>

/*
*物品基类
*class Thing
*/
class Thing Inherit(cocos2d::Node)
{
public:
	Thing(const std::string &name);
	virtual ~Thing();

	/*
	*showDetail();
	*显示物品详情
	*/
	virtual void showDetail(cocos2d::Node* node);

	virtual std::vector<std::string>& getDetails();

	/*
	*物品被使用时调用
	*/
	virtual float beUse(cocos2d::CCObject* obj, cocos2d::CCObject* who = nullptr, cocos2d::CCObject* towho = nullptr);

	static std::string getfileName(const std::string& name);

	virtual bool init() override;

	void addClickCallback(cocos2d::ui::Widget::ccWidgetClickCallback callback);
protected:
	/*
	*initDetails(const std::string& name)
	*初始化细节描述
	*@param name：物品名
	*/
	virtual void initDetails(const std::string& name);

	void onClick(cocos2d::CCObject* sender);

	cocos2d::ui::Widget::ccWidgetClickCallback m_callback;
	//细节描述
	std::vector<std::string> m_details;
	 //购买价格
	PROPERTY__REF(float, m_buyglod, buyglod)
	//卖出价格
	PROPERTY__REF(float, m_sellglod, sellglod)
	//资源路径名称
	PROPERTY__REF(std::string,m_name,name)
	//详情第一句
	PROPERTY__REF(std::string,m_firsttext,firsttext)
};

#endif // !__THING_H__

