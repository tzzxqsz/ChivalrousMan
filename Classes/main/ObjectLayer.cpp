#include"ObjectLayer.h"
#include"tool/Commen.h"
#include"tool/GameData.h"
#include"tool/GameDynamicData.h"
#include"player/CameraPlayer.h"
#include"tool/ReflectNpc.h"
#include"map/MapInfo.h"
#include"task/TaskSystem.h"
#include"player/Player.h"
#include"net/SocketManager.h"
#include"player/PlayerManager.h"
#include"tool/FindRoad.h"
#include<fstream>

ObjectLayer::ObjectLayer()
{

}
  
ObjectLayer::~ObjectLayer()
{
	clearNpcObjectLayer();
}

ObjectLayer* ObjectLayer::createWithLevel(const int& level)
{
	ObjectLayer* pRet = new ObjectLayer;
	if (pRet&&pRet->init(level))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool ObjectLayer::init(const int& level)
{
	if (Layer::init())
	{
		setName("ObjectLayer");
		initNpcObject(level);
		scheduleOnce(schedule_selector(ObjectLayer::initOtherPlayer), 0.5);
		this->scheduleUpdate();
		return true;
	}
	return false;
}

void ObjectLayer::update(float dt)
{
	checkmissedTask();
	checkpickedupTask();
	updateObjectScreenPos();
	checkCollisionNpc();
	checkAddObjectPlayer();
}

void ObjectLayer::initNpcObject(const int& level)
{
	clearNpcObjectLayer();
	char filename[40] = { 0 };
	sprintf_s(filename, "LevelObject/Level%d.lobject", level);
	std::ifstream fin;
	fin.open(filename, std::ios::in);
	if (fin.fail())
	{
		return;
	}
	std::string objname;
	std::string x;
	std::string y;
	fin >> objname;
	do
	{
		fin >> objname;
		fin >> x;
		fin >> y;
		Npc* npc = GET_REFLECT_OBJECT(objname);
		npc->setX(std::stof(x)*MapGridW);
		npc->setY(std::stof(y)*MapGridH);
		Sprite* face = Sprite::create(StringValue(objname));		
		npc->setFace(face);
		m_npcList.push_back(npc);
		this->addChild(face);
	} while (!fin.eof());
	fin.close();
}

void ObjectLayer::initOtherPlayer(float dt)
{
	for (auto var : PlayerManager::getInstance()->getPlayerList())
	{
		if (var.curmap == GetIntData("CurMap"))
		{
			auto player = XGamePlayer::create(var);
			this->addChild(player);
			m_playerlist.push_back(player);
		}
	}
}

void ObjectLayer::clearOtherPlayer()
{
	for (auto var : m_playerlist)
	{
		this->removeChild(var);
	}
	m_playerlist.clear();
}

void  ObjectLayer::checkmissedTask()
{
	for (auto var : m_npcList)
	{
		int index = TaskSystem::getInstance()->haveMissedTask(var->getName());
		if (index)
		{
			var->changeState(NS_HTASK, index);
		}
	}
}

void ObjectLayer::checkpickedupTask()
{
	for (auto var : m_npcList)
	{
		int index = TaskSystem::getInstance()->havePickedupTask(var->getName());
		if (index)
		{
			var->changeState(index > 0 ? NS_STASK : NS_WSTASK, abs(index));
		}
	}
}

void  ObjectLayer::updateObjectScreenPos()
{
	updateNpcScreenPos();
	updateOtherPlayerScreenPos();
}

void ObjectLayer::updateNpcScreenPos()
{
	Vec2 pos;
	for (auto it : m_npcList)
	{
		pos.x = PlayerFacePos().x + (it->getX() - PlayerPos.x);
		pos.y = PlayerFacePos().y + (it->getY() - PlayerPos.y);
		it->getFace()->setPosition(pos);
		float zorder = 100.0f - (it->getY() / MapWidth) * 100;
		it->getFace()->setZOrder(zorder);
	}
}

void ObjectLayer::updateOtherPlayerScreenPos()
{
	Vec2 pos;
	for (auto var : m_playerlist)
	{
		pos.x = PlayerFacePos().x + (var->getWorldPos().x - PlayerPos.x);
		pos.y = PlayerFacePos().y + (var->getWorldPos().y - PlayerPos.y);  
		var->setPosition(pos);
		float zorder = 100.0f - (var->getWorldPos().y / MapWidth) * 100;
		var->setZOrder(zorder);
	}
}

void ObjectLayer::clearNpcObjectLayer()
{
	for (auto it : m_npcList)
	{
		RELEASE_NULL(it);
	}
	m_npcList.clear();
}

void ObjectLayer::addPlayer(Player_Info pinfo)
{
	if (GetIntData("CurMap") == pinfo.curmap)
	{
		auto it = existPlayer(pinfo.playername, pinfo.rolename);
		if (it != m_playerlist.end())
		{
			(*it)->setWorldPos(Vec2{ pinfo.x,pinfo.y });
		}
		else
		{
			auto player = XGamePlayer::create(pinfo);
			this->addChild(player);
			m_playerlist.push_back(player);
		}
	}
	else
	{
		auto it = existPlayer(pinfo.playername, pinfo.rolename);
		if (it != m_playerlist.end())
		{
			this->removeChild(*it);
			m_playerlist.erase(it);
		}
	}
}

void ObjectLayer::removePlayer(const std::string& playername, const std::string& rolename)
{
	for (auto it = m_playerlist.begin(); it != m_playerlist.end(); ++it)
	{
		if ((*it)->getPlayerName() == playername && (*it)->getRoleName() == rolename)
		{
			this->removeChild(*it);
			m_playerlist.erase(it);
			return;
		}
	}
}

std::list<XGamePlayer*>::iterator ObjectLayer::existPlayer(const std::string& playername, const std::string& rolename)
{
	for (auto it = m_playerlist.begin(); it != m_playerlist.end(); ++it)
	{
		if ((*it)->getRoleName() == rolename)
		{
			return it;
		}
	}
	return m_playerlist.end();
}

void ObjectLayer::verifyPlayerPos(const std::string& playername, const std::string& rolename, const cocos2d::Vec2& pos)
{
	for (auto var : m_playerlist)
	{
		if (var->getPlayerName() == playername&&var->getRoleName() == rolename)
		{
			var->setWorldPos(pos);
			return;
		}
	}
}

void ObjectLayer::updatePlayerData(const std::string& playername, const std::string& rolename, Player_Info msg)
{
	for (auto var : m_playerlist)
	{
		if (var->getPlayerName() == playername&&var->getRoleName() == rolename)
		{
			var->setAttack(msg.attack);
			var->setBlood(msg.blood);
			var->setDefense(msg.defense);
			var->setMana(msg.mana);
			return;
		}
	}
}

void ObjectLayer::moveOtherPlayer(const std::string& playername, const std::string& rolename, const cocos2d::Vec2& target,int less)
{
	for (auto var : m_playerlist)
	{
		if (var->getPlayerName() == playername&&var->getRoleName() == rolename)
		{
			var->moveTo(target, less);
		}
	}
}

Npc* ObjectLayer::findNpcByName(const std::string& name)
{
	for (auto var : m_npcList)
	{
		if (var->getName() == name)
		{
			return var;
		}
	}
	return nullptr;
}

void ObjectLayer::checkCollisionNpc()
{
	for each (auto var in m_npcList)
	{
		float dis = ccpDistance(PlayerPos, ccp(var->getX(), var->getY()));
		if (dis < 120)
		{
			if (!var->getIsCollision())
			{
				var->collisionEvent();
			}
		}
		else
		{
			if (var->getIsCollision())
			{
				var->endCollisionEvent();
			}
		}
	}
}

void ObjectLayer::checkAddObjectPlayer()
{
	if (PlayerManager::getInstance()->getAddList().size() > 0)
	{
		for (auto var : PlayerManager::getInstance()->getAddList())
		{
			addPlayer(var);
		}
		PlayerManager::getInstance()->getAddList().clear();
	}
}
