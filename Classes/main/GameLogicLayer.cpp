#include"GameLogicLayer.h"
#include"tool/Commen.h"
#include"player/CameraPlayer.h"
#include"map/MapInfo.h"
#include"tool/GameData.h"
#include"base/Door.h"
#include"tool/GameDynamicData.h"
#include"ExcessiveScene.h"
#include"GameScene.h"
#include"ObjectLayer.h"
#include"fight/FightLayer.h"
#include"net/SocketManager.h"
#include"team/TeamManager.h"
#include"player/PlayerManager.h"
#include"common/TipLayer.h"
#include"event/SignalConst.h"
#include"event/SignalManager.h"
#include<stack>
#include<functional>

#define UpdateSpeed 240

bool GameLogicLayer::init()
{
	if (Layer::init())
	{
		m_unTouch = false;
		LISTEN_TOUCH(GameLogicLayer);
		scheduleUpdate();
		return true;
	}
	return false;
}

void  GameLogicLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (m_unTouch)
		return;
	if (PlayerTeamStatus() == P_STATUS_MEMBER)
	{
		auto tiplayer = TipLayer::createTipLayer(StringValue("TeamingText"));
		CurGameScene()->addChild(tiplayer);
		return;
	}
	Vec2 pos = touch->getLocation();
	Vec2 targetPos{ PlayerPos.x + (pos.x - GetPlayerFace()->getPosition().x),PlayerPos.y + (pos.y - GetPlayerFace()->getPosition().y) };
	bool bRet=CameraPlayer::getPlayerInstance()->moveTo(targetPos);
	if (CameraPlayer::getPlayerInstance()->getTeamStatus() == P_STATUS_HEADER&&bRet)
	{
		std::function<void(float)> func = [targetPos](float) {
			CameraPlayer::getPlayerInstance()->moveTeamMembers(targetPos);
		};
		scheduleOnce(func, 0.1, "movemember");
	}
}

void GameLogicLayer::update(float dt)
{
	if (checkEntryFight())
		return;
	if (checkEntryDoor())
		return;
	if (PlayerCanMove())
	{
		PlayerMove();
		randomMeetMonster();
	}
	checkTip();
}

bool GameLogicLayer::checkEntryDoor()
{
	if (checkGotoMap())
		return true;
	if (PlayerTeamStatus() == P_STATUS_MEMBER)
		return false;
	std::vector<Door> doors = GetDoorPosInfo();
	int size = doors.size();
	int count = 0;
	for (int i = 0; i <size; ++i)
	{
		float dis = ccpDistance(PlayerPos, ccp(doors[i].x, doors[i].y));
		if (dis < 40)
		{
			SetFloatData("DestX", doors[i].destPos.x);
			SetFloatData("DestY", doors[i].destPos.y);
			SetIntData("IsDoor", 1);
			gotoDestMap(doors[i].dest);
			return true;
		}
	}
	return false;
}

void GameLogicLayer::gotoDestMap(const std::string& dest)
{
	getParent()->cleanup();
	SetIntData("IsHaveGameScene", 0);
	std::function<bool(void)> func = [] {return true; };
	ExcessiveScene* ex = nullptr;

	if (PlayerTeamStatus() == P_STATUS_HEADER)
	{
		for (auto var : TeamManager::getInstance()->getTeamMembers())
		{
			auto info = PlayerManager::getInstance()->findPlayerInfoByFd(var.first);
			Vec2 target{ GetFloatData("DestX"),GetFloatData("DestY") };
			TeamManager::getInstance()->c2sTeamGotoMap(dest, target, var.first);
		}
	}
	if (dest == "map1")
	{
		ex = ExcessiveScene::createExcessice(LEVEL_ONE, func, 1);
	}
	else if (dest == "map2")
	{
		ex = ExcessiveScene::createExcessice(LEVEL_TWO, func, 1);
	}
	else if (dest == "map3")
	{
		ex = ExcessiveScene::createExcessice(LEVEL_THREE, func, 1);
	}
	else if (dest == "map4")
	{
		ex = ExcessiveScene::createExcessice(LEVEL_FOUR, func, 1);
	}
	else if (dest == "map5")
	{
		ex = ExcessiveScene::createExcessice(LEVEL_FIVE, func, 1);
	}
	Director::getInstance()->replaceScene(ex);
}

void GameLogicLayer::randomMeetMonster()
{
	if (PlayerTeamStatus() == P_STATUS_MEMBER)
		return;
	//����������
	static int interval = 0;
	std::random_device rand;
	if (GetIntData("CurMap")>=LEVEL_THREE)
	{
		if (interval > 5)
		{
			int randnum = rand() % 100;
			if (randnum < 2)
			{
				int nums = rand() % 4 + 1;
				std::string name = monsterName();
				SetIntData("IsEntryFight", 1);
				SetIntData("MonsterNums", nums);
				SetStringData("MonsterName", name);
				checkTeamEntryFight(name, nums);
			}
			interval = 0;
		}
	}
	interval++;
}

std::string  GameLogicLayer::monsterName()
{
	std::random_device rand;
	switch (GetIntData("CurMap"))
	{
	case LEVEL_THREE:
	{
		std::string name[] = { "Ghost","BlackDragon","Dragon" };
		int index = rand() % 3;
		return name[index];
	}
	case LEVEL_FOUR:
	{
		std::string name[] = { "Kougamon","Lion","Minotaur" };
		int index = rand() % 3;
		return name[index];
	}
	case LEVEL_FIVE:
	{
		std::string name[] = { "Octopus","Pterosaur","SkeletonMaster","TarrasqueMessenger" };
		int index = rand() % 4;
		return name[index];
	}
	default:
		return "";
	}
}

bool GameLogicLayer::checkGotoMap()
{
	if (TeamManager::getInstance()->getGotoMapMsgs().size() > 0)
	{
		TeamGotoMap msg = TeamManager::getInstance()->getGotoMapMsgs().back();
		SetFloatData("DestX", msg.x);
		SetFloatData("DestY", msg.y);
		SetIntData("IsDoor", 1);
		TeamManager::getInstance()->getGotoMapMsgs().clear();
		gotoDestMap(msg.map);
		return true;
	}
	return false;
}

void GameLogicLayer::checkTeamEntryFight(const std::string& name, const int& nums)
{
	if (PlayerTeamStatus() == P_STATUS_HEADER)
	{
		for (auto var : TeamManager::getInstance()->getTeamMembers())
		{
			TeamManager::getInstance()->c2sTeamFight(var.first, name, nums);
		}
	}
}

bool GameLogicLayer::checkEntryFight()
{
	if (GetIntData("IsEntryFight") == 1)
	{
		getParent()->cleanup();
		SetFloatData("DestX", PlayerPos.x);
		SetFloatData("DestY", PlayerPos.y);
		SetIntData("IsHaveGameScene", 0);
		SetIntData("IsEntryFight", 0);
		CCLayerColor* red = CCLayerColor::create(ccc4(255, 0, 0, 128));
		red->setName("redLayer");
		CurGameScene()->addChild(red);
		std::function<void(float)> func = [this](float) {
			CurGameScene()->removeChildByName("redLayer");
			auto fightscene = FightLayer::createFightScene(GetStringData("MonsterName"), GetIntData("MonsterNums"));
			auto reScene = TransitionFadeDown::create(1, fightscene);
			Director::sharedDirector()->replaceScene(reScene);
		};
		scheduleOnce(func, 0.2, "red");
		return true;
	}
	return false;
}

void GameLogicLayer::checkTip()
{
	if (GetIntData("IsHaveTip") == 1)
	{
		SetIntData("IsHaveTip", 0);
		TipLayer* tiplayer = TipLayer::createTipLayer(GetStringData("TipText"));
		getParent()->addChild(tiplayer);
	}
}

void  GameLogicLayer::onEnter()
{
	Layer::onEnter();
}

void  GameLogicLayer::onExit()
{
	Layer::onExit();
}
