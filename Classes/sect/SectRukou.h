#pragma once
#ifndef __SECT_RU_KOU_H__
#define __SECT_RU_KOU_H__
#include"tool/PreProcess.h"
#include"ui/UIImageView.h"

class SectRukou :public cocos2d::Node
{
public:
	CREATE_FUNC(SectRukou)

	bool init() override;

	void updateUI(const std::string& name);

	void addJoinClickCallback(cocos2d::ui::Widget::ccWidgetClickCallback callback);

	cocos2d::Size getRokouSize();
private:
	void onJoinClickCallback(cocos2d::CCObject* sender);

	void updateDec(const std::string& name);

	cocos2d::ui::ImageView* m_image;
	cocos2d::Label* m_textname;
	cocos2d::ui::Widget::ccWidgetClickCallback m_callback = nullptr;
};

#endif // !__SECT_RU_KOU_H__
