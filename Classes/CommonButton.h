#pragma once
#ifndef __COMMON_BUTTON_H__
#define __COMMON_BUTTON_H__
#include"PreProcess.h"
#include"ui/UIButton.h"

class CommonButton :public cocos2d::Node
{
public:
	CreateWithParam(CommonButton, std::string)

	bool init(std::string res);

	void addClickCallback(cocos2d::ui::Widget::ccWidgetClickCallback callback);

	virtual void onEnter() override;
	
	void showRedPoint(const bool& visible);

	virtual void setContentSize(const cocos2d::Size& size) override;
private:
	void onClickCallback(cocos2d::CCObject* sender);

	cocos2d::Sprite* m_spot;
	cocos2d::ui::Button* m_btn;
	cocos2d::ui::Widget::ccWidgetClickCallback m_callback = nullptr;
};

#endif // !__COMMON_BUTTON_H__

