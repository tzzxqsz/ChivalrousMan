#pragma once
#ifndef __TALISMAN_LAYER_H__
#define __TALISMAN_LAYER_H__
#include"PreProcess.h"
#include"CommonTouchLayer.h"

class TalismanAvatar;
class CommonButton;
class TalismanFragment;
class CommonProcessBar;

class TalismanLayer:public CommonTouchLayer
{
	CLASS_ESSENTAIL(TalismanLayer)
public:
	CREATE_FUNC(TalismanLayer)
	
	bool init() override;
	
	virtual void onEnter() override;

	void updateView();

	void updateDes(const std::string& name);

	void onLeftClickCallback(cocos2d::CCObject* sender);
	
	void onRightClickCallback(cocos2d::CCObject* sender);

	void onBattleClickCallback(cocos2d::CCObject* sender);

	void onSynthesisClickCallback(cocos2d::CCObject* sender);

	void updateArrow();

	void updateButton(const bool& isInBattle);
private:
	cocos2d::Label* m_tilasmanName;
	cocos2d::Label* m_tilsmanGrade;
	cocos2d::Node* m_desc;
	CommonButton* m_leftArrow;
	CommonButton* m_rightArrow;
	CommonButton* m_battleBtn;
	CommonButton* m_synthesisBtn;
	CommonProcessBar* m_progress;
	int m_curIndex;
	TalismanFragment* m_fragment;
	TalismanAvatar* m_avatar;
};


#endif // !__TALISMAN_LAYER_H__

