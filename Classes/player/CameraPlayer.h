#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include"base/Animal.h"
#include"PlayerData.h"
#include<iostream>
#include<utility>
#include<stack>

#define GetPlayerFace CameraPlayer::getPlayerInstance()->getFace
#define SetPlayerFace CameraPlayer::getPlayerInstance()->setFace
#define PlayerTrunDir CameraPlayer::getPlayerInstance()->trunDir
#define SetPlayerVelocity CameraPlayer::getPlayerInstance()->setVelocity
#define PlayerPos CameraPlayer::getPlayerInstance()->getPos()
#define PlayerMove CameraPlayer::getPlayerInstance()->move
#define PlayerCanMove CameraPlayer::getPlayerInstance()->canMove
#define SetPlayerMoveRoad CameraPlayer::getPlayerInstance()->setMoveRoad
#define PlayerDir CameraPlayer::getPlayerInstance()->getDir
#define PlayerFacePos CameraPlayer::getPlayerInstance()->getFacePos
#define InitPlayerState CameraPlayer::getPlayerInstance()->initStateInfo
#define GetPlayerData CameraPlayer::getPlayerInstance()->getPlayerData
#define AttackPlayer CameraPlayer::getPlayerInstance()->beAttack
#define PlayerTeamStatus CameraPlayer::getPlayerInstance()->getTeamStatus

class PlayerState;

/*
class CameraPlayer 
*主角类，同时充当摄像机
*/
class CameraPlayer :public Animal
{
public:
	/*
	*获取摄像机玩家的对象
	*/
	static CameraPlayer* getPlayerInstance();

	inline cocos2d::Vec2 getFacePos() { return  m_face->getPosition(); }

	/*
	*设置玩家的UI
	*/
	void setFace(cocos2d::Sprite* face);

	/*
	*getFace()
	*获取玩家的UI
	*@return Sprite*：得到的UI
	*/
	inline cocos2d::Sprite* getFace() { return m_face; }

	/*
	*changeMapPosToUI();
	*将玩家和地图在世界坐标上的位置转化到UI屏幕上
	*@return std::pair<cocos2d::Vec2,cocos2d::Vec2>：返回
	*/
	std::pair<cocos2d::Vec2,cocos2d::Vec2>  changeMapPosToUI();

	/*
	*move
	*移动
	*@return bool：是否真的移动了
	*/
	bool move() override;
	
	/*
	*释放该类
	*释放玩家实例对象
	*/
	static void release();

	/*
	*canMove()
	*判断是否可以移动
	*/
	bool canMove();

	/*
	*trunDir(const float& angle)
	*转向
	*@param angle：转向角度
	*/
	bool trunDir(const float& angle) override;
	
	/*
	*setMoveRoad(stack<Vec2> road
	*设置当前的移动路径
	*@param road：移动路径
	*/
	void setMoveRoad(std::stack<cocos2d::Vec2>& road);

	/*
	*CalcAngle(cocos2d::Vec2,cocos2d::Vec2);
	*计算两点之间的夹角
	*@param start:起始点
	*@param target:终点
	*@return float:返回夹角的弧度值
	*/
	float CalcAngle(cocos2d::Vec2 start, cocos2d::Vec2 target);

	/*
	*initStateInfo();
	*初始化状态信息
	*@param level:不同地图层
	*/
	void initStateInfo(const int& level);

	/*
	*获取玩家数据
	*/
	PlayerData& getPlayerData() { return m_playerData; }
	
	/*
	*beAttack(float attack);
	*玩家被攻击
	*@param attack：攻击伤害
	*/
	void beAttack(float attack);

	/*
	*SaveGameData();
	*持久化保存游戏角色数据
	*/
	void SaveGameData();

	/*
	*MoveTo(const cocos2d::Vec2& targetPos);
	*移到某点
	*@param targetPos:将要移动到的目标地点世界地图坐标
	*@param less：是否少移动一格
	*@return bool：返回true表示可以移动到，返回false表示不可
	*/
	bool moveTo(cocos2d::Vec2 targetPos, int less = 0);

	/*
	*移动队伍成员
	*@param target：移动的目的地
	*/
	void moveTeamMembers(cocos2d::Vec2 target);

	/*
	*clearRoadList();
	*清空路径队列
	*/
	void clearRoadList();
private:
	/*
	*AdjustPlayerAndMapPos()
	*调整玩家和地图的位置
	*/
	void AdjustPlayerAndMapPos();

	/*
	*goNext();
	*前往下一个节点
	*/
	void goNext();

	CameraPlayer();
	~CameraPlayer();

	//玩家UI
	cocos2d::Sprite* m_face = nullptr;

	//主角实例
	static CameraPlayer* m_instance;

	//移动路径列表
	std::stack<cocos2d::Vec2> m_roadList;

	//玩家状态
	PlayerState* m_state = nullptr;

	//标记状态改变
	int m_flag;
	//保存玩家数据
	PlayerData m_playerData;
	//玩家队伍状态
	PROPERTY__REF(int, m_teamStatus, TeamStatus)
};

#endif // !__PLAYER_H__