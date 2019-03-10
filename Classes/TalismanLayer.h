#pragma once
#ifndef __TALISMAN_LAYER_H__
#define __TALISMAN_LAYER_H__
#include"PreProcess.h"
#include"CommonTouchLayer.h"

class TalismanAvatar;

class TalismanLayer:public CommonTouchLayer
{
	CLASS_ESSENTAIL(TalismanLayer)
public:
	CREATE_FUNC(TalismanLayer)
	
	bool init() override;
	
	virtual void onEnter() override;

	void updateView();

	void updateDes();

	void onLeftClickCallback(cocos2d::CCObject* sender);
	
	void onRightClickCallback(cocos2d::CCObject* sender);
private:
	cocos2d::Label* m_tilasmanName;
	cocos2d::Label* m_tilsmanGrade;
	cocos2d::Node* m_desc;

	TalismanAvatar* m_avatar;
};


#endif // !__TALISMAN_LAYER_H__

