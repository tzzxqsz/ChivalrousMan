#include"SelectScene.h"
#include"tool/Commen.h"
#include"SelectLayer.h"
#include"tool/GameData.h"

bool SelectScene::init()
{
	if (Scene::init())
	{
		auto stLayer = SelectLayer::create();
		this->addChild(stLayer);
		return true;
	}
	
	return false;
}