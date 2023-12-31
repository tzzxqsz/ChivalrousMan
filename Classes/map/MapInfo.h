#pragma once
#ifndef __MAP_INFO_H__
#define __MAP_INFO_H__
#include"tool/PreProcess.h"
#include<vector>

class GameMapLayer;
class Door;

#define LoadMapInfo MapInfo::getMapInstance()->readMapInfoFromFile
#define MapCountX MapInfo::getMapInstance()->getCountx()
#define MapCountY MapInfo::getMapInstance()->getCounty()
#define MapTexturesNum MapInfo::getMapInstance()->getTextureNum()
#define MapWidth MapInfo::getMapInstance()->getMapWidth()
#define MapHeight MapInfo::getMapInstance()->getMapHeight()
#define MapInterval MapInfo::getMapInstance()->getInterval()
#define InitMapLayer MapInfo::getMapInstance()->setMapLayer
#define MapLayerObject MapInfo::getMapInstance()->getMapLayer()
#define MapGridW MapInfo::getMapInstance()->getMapGridW()
#define MapGridH MapInfo::getMapInstance()->getMapGridH()
#define GetMapInfo MapInfo::getMapInstance()->getMapInfo
#define GetDoorPosInfo MapInfo::getMapInstance()->getDoorPosInfo
#define UpdateDoorScreenPos MapInfo::getMapInstance()->updateDoorsScreenPos
#define LoadDoorInfo MapInfo::getMapInstance()->loadDoorInfo

class MapInfo:public cocos2d::CCObject
{
public:
	static MapInfo* getMapInstance();

	static void release();

	bool readMapInfoFromFile(const std::string& filename);
	
	void setMapLayer(GameMapLayer* maplayer);

	inline GameMapLayer* getMapLayer() { return m_mapLayer; }

	inline int getMapGridW() { return m_mapSize.width / m_countx; }

	inline int getMapGridH() { return m_mapSize.height / m_county; }
	
	inline int getCountx() { return m_countx; }

	inline int getCounty() { return m_county; }

	inline int getTextureNum() { return m_maptextures; }

	inline float getMapWidth() { return m_mapSize.width; }

	inline float getMapHeight() { return m_mapSize.height; }
	
	inline int** getMapInfo() { return m_mapinfo; }

	inline float getInterval() { return m_mapSize.width / m_maptextures; }

	std::vector<Door>& getDoorPosInfo() { return m_doorPos; }

	/*
	*updateDoorsScreenPos
	*更新传送门在屏幕上的位置信息
	*/
	void updateDoorsScreenPos();

	/*
	*loadDoorInfo(const std::string& name);
	*从文件加载地图信息
	*/
	void loadDoorInfo(const std::string& name);

	cocos2d::Vec2 getDestMapPos(const std::string& mapname);
private:
	/*
	*releaseMapInfo();
	*释放地图信息
	*/
	void releaseMapInfo();

	/*
	*reset()
	*重置
	*/
	void reset();

	MapInfo();
	~MapInfo();

	int m_maptextures;
	GameMapLayer* m_mapLayer = nullptr;
	cocos2d::Size m_mapSize;
	int** m_mapinfo = nullptr;
	int m_countx;
	int m_county;
	std::vector<Door> m_doorPos;

	static MapInfo* m_instance;
};

#endif // !__MAP_INFO_H__


