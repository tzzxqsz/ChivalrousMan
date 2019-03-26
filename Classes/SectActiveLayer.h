#pragma once
#ifndef __SEACT_ACTIVE_LAYER_H__
#define __SEACT_ACTIVE_LAYER_H__
#include"PreProcess.h"
#include"ui/UIImageView.h"

class SectActiveLayer :public cocos2d::Layer
{
public:
	CREATE_FUNC(SectActiveLayer)

    bool init() override;

	void updateUI(const std::string& name);
private:
	void updateDec();

	void updateAttrs();

	cocos2d::ui::ImageView* m_imageBg;
	cocos2d::Node* m_nodeDec;
	cocos2d::Label* m_title;
	std::string m_name;
};

#endif // !__SEACT_ACTIVE_LAYER_H__

