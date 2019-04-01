#pragma once
#ifndef __XIULIAN_LAYER_H__
#define __XIULIAN_LAYER_H__
#include"CommonTouchLayer.h"

class XiulianLayer :public CommonTouchLayer
{
public:
	CREATE_FUNC(XiulianLayer)

	bool init() override;

	void onEnter() override;

	void onExit() override;
private:

	
};

#endif // !__XIULIAN_LAYER_H__

