#pragma once
#ifndef __BEGIN_LAYER_H__
#define __BEGIN_LAYER_H__
#include"tool/PreProcess.h"

/*
*class BeginLayer
*��Ϸ�Ŀ�ʼ�����
*/
class BeginLayer Inherit(cocos2d::Layer)
{
	CLASS_ESSENTAIL(BeginLayer);
	CREATE_FUNC(BeginLayer);
public:
	bool init() override;

	/*
	*��¼��ť�ص�����
	*/
	void onLoginCallBack(cocos2d::CCObject* sender);

	/*
	*ע�ᰴť�ص�����
	*/
	void onSigonCallBack(cocos2d::CCObject* sender);

	/*
	*�������ֿ��ػص�����
	*/
	void onMusicOnOrOffCallBack(cocos2d::CCObject* sender);

	void showBtn();

	cocos2d::MenuItemLabel* loginBtn;
    cocos2d::MenuItemLabel* sigonBtn;
};

#endif // !__BEGIN_LAYER_H__
