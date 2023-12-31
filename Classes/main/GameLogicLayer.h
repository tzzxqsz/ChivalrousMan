#pragma once
#ifndef __GAME_LOGIC_LAYER_H__
#define __GAME_LOGIC_LAYER_H__
#include"tool/PreProcess.h"
#include<string>

/*
*class GameLogicLayer
*游戏逻辑层，处理游戏中的大部分逻辑
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
	*检查是否进入门内，并处理相应事件
	*/
	bool checkEntryDoor();



	/*
	*gotoDestMap
	*切换到目标地图
	*@param dest：目标名
	*/
	void gotoDestMap(const std::string& dest);

	/*
	*randomMeetMonster();
	*在野怪区随机遇见怪物
	*/
	void randomMeetMonster();

	/*
	*monsterName();
	*生成遇到怪物的名字
	*/
	std::string monsterName();

	/*
	*检查前往某地图
	*/
	bool checkGotoMap();
	
	/*
	*
	*/
	void checkTeamEntryFight(const std::string& name,const int& nums);

	/*
	*检查是否进入战斗
	*/
	bool checkEntryFight();

	/*
	*checkTip();
	*检查是否有提示
	*/
	void checkTip();

	PROPERTY__REF(bool, m_unTouch, UnTouch);
};

#endif // !__GAME_LOGIC_LAYER_H__