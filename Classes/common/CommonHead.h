#pragma once
#ifndef __COMMON_HEAD_H__
#define __COMMON_HEAD_H__
#include"tool/PreProcess.h"
#include"ui/UIWidget.h"

struct Player_Info;

class CommonHead:public cocos2d::Node
{
public:
	CommonHead();
	~CommonHead();

	CreateWithParam(CommonHead, Player_Info);

	bool init(const Player_Info& info);

	void onHeadClick(cocos2d::CCObject* sender);

	void setCallback(cocos2d::ui::Widget::ccWidgetClickCallback& callback);
private:
	cocos2d::ui::Widget::ccWidgetClickCallback m_callback = nullptr;
};
#endif // !__COMMON_HEAD_H__

