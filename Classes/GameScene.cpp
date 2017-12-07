#include"GameScene.h"
#include"GameData.h"
#include"GameMapLayer.h"
#include"GameLogicLayer.h"
#include"CameraPlayer.h"
#include"Commen.h"

bool GameScene::init()
{
	if (Scene::init())
	{
		auto gamemap = GameMapLayer::create();
		gamemap->loadMapTexture("map1");
		gamemap->drawMap(0, 0);
		this->addChild(gamemap);

		auto player = Sprite::create();
		auto animation = AnimationCache::getInstance()->getAnimation("Player1");
		auto animate = Animate::create(animation);
		player->runAction(RepeatForever::create(animate));
		this->addChild(player);
		SetPlayerVelocity(4);
		SetPlayerFace(player);

		auto logicLayer = GameLogicLayer::create();
		this->addChild(logicLayer);
		return true;
	}
	return false;
}