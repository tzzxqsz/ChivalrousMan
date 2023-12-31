#pragma once
#ifndef __SECT_MAIN_LAYER_H__
#define __SECT_MAIN_LAYER_H__
#include"common/CommonTouchLayer.h"

class SectMainLayer :public CommonTouchLayer
{
public:
	CREATE_FUNC(SectMainLayer)

	bool init() override;

	void onBackClickCallback(cocos2d::CCObject* sender);

	void onClickJoinSectCallback(cocos2d::CCObject* sender);
private:
	void gotoSectActiveLayer();

};

#endif // !__SECT_MAIN_LAYER_H__

