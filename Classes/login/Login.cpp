#include"Login.h"
#include"tool/GameData.h"
#include"LoginLayer.h"
#include"tool/Commen.h"

bool Login::init()
{
	if (Scene::init())
	{
		auto loginLayer = LoginLayer::create();
		this->addChild(loginLayer);
		return true;
	}
	return false;
}