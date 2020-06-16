#pragma once
#ifndef __MINI_MAP_LAYER_H__
#define __MINI_MAP_LAYER_H__
#include"tool/PreProcess.h"
#include"common/CommonTouchLayer.h"
#include<string>
#include<map>

struct stMap
{
	cocos2d::Vec2 pos;
	std::string name;
};

/*
*class WorldMapLayer
*��ʾ����ֲ�ͼ
*/
class WorldMapLayer Inherit(CommonTouchLayer)
{
	CLASS_ESSENTAIL(WorldMapLayer)
	CREATE_FUNC(WorldMapLayer)
public:
	virtual bool init() override;
	
private:
	/*
	*��ʼ����ʾ��ͼ����
	*/
	void  initMapInfo();

	std::map<std::string, stMap> m_maps;
};

#endif // !__MINI_MAP_LAYER_H__
