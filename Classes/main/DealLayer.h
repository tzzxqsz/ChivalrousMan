#pragma once
#ifndef __DEAL_LAYER_H__
#define __DEAL_LAYER_H__
#include"tool/PreProcess.h"
#include"common/CommonTouchLayer.h"
#include"base/Thing.h"
#include<vector>
#include<string>

/*
*class DealLayer
*���ײ�
*/
class DealLayer Inherit(CommonTouchLayer)
{
	CLASS_ESSENTAIL(DealLayer)
public:
	/*
	*���ݴ������ʹ���һ����Ʒ���ײ�
	*@param type��ָ����������
	*/
	static DealLayer* createWithType(const int& type,const std::string& name);

	bool init(const int& type, const std::string& name);
private:
	/*
	*checkBuy(float money);
	*����Ƿ���Թ���
	*@param money����Ʒ�۸�
	*/
	void checkBuy(float money);

	/*
	*����ť�ص�����
	*/
	void onBuyBtnCallBack(cocos2d::CCObject* sender);
	
	/*
	*onCloseBtnCallBack(cocos2d::CCObject* sender);
	*�رհ�ť�ص�����
	*/
	void onCloseBtnCallBack(cocos2d::CCObject* sender);

	/*
	*��ʼ�����ײ����Ʒ
	*/
	void initThingByName(const int& type,const std::string& name);

	/*
	*�����Ʒ�Ļص�����
	*/
	void onClickThingCallBack(cocos2d::CCObject* sender);
	
	//��������
	int m_type;
	cocos2d::Vec2 m_basePoint;
	cocos2d::Sprite* m_selector;
	cocos2d::Menu* menu;
	cocos2d::CCObject* m_curSelect = nullptr;
};

#endif // !__DEAL_LAYER_H__