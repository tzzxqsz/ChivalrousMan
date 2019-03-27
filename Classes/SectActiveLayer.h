#pragma once
#ifndef __SEACT_ACTIVE_LAYER_H__
#define __SEACT_ACTIVE_LAYER_H__
#include"CommonTouchLayer.h"
#include"ui/UIImageView.h"
#include"ui/UIButton.h"

class SectActiveLayer :public CommonTouchLayer
{
public:
	CREATE_FUNC(SectActiveLayer)

    bool init() override;

	void updateUI(const std::string& name);

	void onBackClickCallback(cocos2d::CCObject* sender);

	void onXiulianClickCallback(cocos2d::CCObject* sender);

	void onGongfaClickCallback(cocos2d::CCObject* sender);
private:
	void updateDec();

	void updateAttrs();

	cocos2d::ui::ImageView* m_imageBg;
	cocos2d::Node* m_nodeDec;
	cocos2d::Label* m_title;
	cocos2d::ui::Button* m_xiulian;
	cocos2d::ui::Button* m_gongfa;
	std::string m_name;
};

#endif // !__SEACT_ACTIVE_LAYER_H__

