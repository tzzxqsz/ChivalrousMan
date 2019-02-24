#pragma once
#ifndef __COMMON_TOUCH_LAYER_H__
#define __COMMON_TOUCH_LAYER_H__
#include"PreProcess.h"

class CommonTouchLayer :public cocos2d::LayerColor
{
public:
	CREATE_FUNC(CommonTouchLayer);

	virtual bool init() override;

	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) override;

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event) override;

	void setTouchClose(const bool& touchClose = true);

	void setExcludeRect(const cocos2d::Point& center, const cocos2d::Rect& rect);
private:
	bool m_touchClose = true;

	cocos2d::Rect m_excludeRect;
};


#endif // !

