#include"TalismanLayer.h"


bool TalismanLayer::init()
{
	if (CommonTouchLayer::init())
	{
		return true;
	}
	return false;
}

void TalismanLayer::onEnter()
{
	CommonTouchLayer::onEnter();
	
}
