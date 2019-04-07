#include"NewGameScene.h"
#include"tool/Commen.h"
#include"NewGameLayer.h"

bool NewGameScene::init()
{
	if (Scene::init())
	{
		auto newLayer = NewGameLayer::create();
		this->addChild(newLayer);
		return true;
	} 
	return false;
}