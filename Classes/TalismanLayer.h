#pragma once
#ifndef __TALISMAN_LAYER_H__
#define __TALISMAN_LAYER_H__
#include"PreProcess.h"
#include"CommonTouchLayer.h"

class TalismanLayer:public CommonTouchLayer
{
	CLASS_ESSENTAIL(TalismanLayer)
public:
	CREATE_FUNC(TalismanLayer)
	
	bool init() override;
	
	virtual void onEnter() override;
private:
	
};


#endif // !__TALISMAN_LAYER_H__

