#include"GameMapLayer.h"
#include"GameData.h"
#include"GameDynamicData.h"
#include"Commen.h"
#include"MapInfo.h"
#include"CameraPlayer.h"
#include"GameLogicLayer.h"
#include<sstream>

#define UpdateSpeed 60

bool GameMapLayer::init()
{
	if (Layer::init())
	{
		auto back = Sprite::create(StringValue("GameBg"), Rect{ 0,0,SCREEN.width,SCREEN.height });
		back->setPosition(SCREEN.width*0.5, SCREEN.height*0.5);
		this->addChild(back);

		m_curMaps = Node::create();
		this->addChild(m_curMaps);
		return true;
	}
	return false;
}

bool GameMapLayer::loadMapTexture(std::string name)
{
	LoadMapInfo(StringValue(name));
	char filename[40] = { 0 };
	for (int i = 1; i <=MapTexturesNum; ++i)
	{
		sprintf_s(filename, "%s/%s_%d.png", name.c_str(), name.c_str(), i);
		auto mapframe = Sprite::create(filename);
		mapframe->setAnchorPoint(ccp(0, 0));
		m_curMaps->addChild(mapframe);
		m_mapList.push_back(mapframe);
	}
	InitMapLayer(this);
	return true;
}

void GameMapLayer::resetMap()
{
	for (int i = 0; i < m_mapList.size(); ++i)
	{
		m_mapList[i]->setPosition(-MapInterval, 0);
	}
}

bool GameMapLayer::drawMap(float startx, float starty)
{
	resetMap();
	int width = SCREEN.width;
	float mapinterval = MapInterval;
	int start = startx / mapinterval;
	float realstartx = startx - start*mapinterval;
	NEGATE(realstartx);
	NEGATE(starty);
	int num = width / mapinterval;
	for (int i = 0; i<=num; ++i)
	{
		m_mapList[i + start]->setPosition(realstartx + i*mapinterval, starty);
	}
	return true;
}