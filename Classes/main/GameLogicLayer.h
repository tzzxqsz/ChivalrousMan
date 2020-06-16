#pragma once
#ifndef __GAME_LOGIC_LAYER_H__
#define __GAME_LOGIC_LAYER_H__
#include"tool/PreProcess.h"
#include<string>

/*
*class GameLogicLayer
*��Ϸ�߼��㣬������Ϸ�еĴ󲿷��߼�
*/
class GameLogicLayer Inherit(cocos2d::Layer)
{
	CLASS_ESSENTAIL(GameLogicLayer);
public:
	CREATE_FUNC(GameLogicLayer);

	virtual bool init();

	void update(float dt);

	virtual void onEnter() override;

	virtual void onExit() override;
private:
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	/*
	*CheckEntryDoor();
	*����Ƿ�������ڣ���������Ӧ�¼�
	*/
	bool checkEntryDoor();



	/*
	*gotoDestMap
	*�л���Ŀ���ͼ
	*@param dest��Ŀ����
	*/
	void gotoDestMap(const std::string& dest);

	/*
	*randomMeetMonster();
	*��Ұ���������������
	*/
	void randomMeetMonster();

	/*
	*monsterName();
	*�����������������
	*/
	std::string monsterName();

	/*
	*���ǰ��ĳ��ͼ
	*/
	bool checkGotoMap();
	
	/*
	*
	*/
	void checkTeamEntryFight(const std::string& name,const int& nums);

	/*
	*����Ƿ����ս��
	*/
	bool checkEntryFight();

	/*
	*checkTip();
	*����Ƿ�����ʾ
	*/
	void checkTip();

	PROPERTY__REF(bool, m_unTouch, UnTouch);
};

#endif // !__GAME_LOGIC_LAYER_H__