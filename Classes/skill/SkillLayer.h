#pragma once
#ifndef __SKILL_LAYER_H__
#define __SKILL_LAYER_H__
#include"tool/PreProcess.h"
#include"common/CommonTouchLayer.h"
#include<vector>

/**
*class SkillLayer
*��ʾ��Ҽ���
*/
class SkillLayer Inherit(CommonTouchLayer)
{
	CLASS_ESSENTAIL(SkillLayer)
	CREATE_FUNC(SkillLayer)
public:
 	virtual bool init() override;

private:
	/*
	*initSkillIcon()
	*��ʼ������ͼ��
	*/
	void initSkillIcon();

	/*
	*onSkillCkickCallBack(cocos2d::CCObject* sender);
	*����ͼ�����ص�����
	*/
	void onSkillCkickCallBack(cocos2d::CCObject* sender);

	/*
	*�������ܰ�ť����ص�����
	*/
	void onBtnUpClickCallback(cocos2d::CCObject* sender);

	cocos2d::Menu* m_menu;
	cocos2d::Vec2 m_basePos;
	cocos2d::Sprite* m_selector;
	cocos2d::CCObject* m_selectedSkill;
	std::vector<cocos2d::LabelTTF*> m_gradelabels;
	std::vector<cocos2d::LabelTTF*> m_upskillGlods;
};

#endif // !__SKILL_LAYER_H__
