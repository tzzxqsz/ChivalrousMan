#include"PlayerState.h"
#include"Commen.h"
#include"GameDynamicData.h"

PlayerState::PlayerState(cocos2d::Sprite* face)
{
	m_playerFace = face;
}

PlayerState::~PlayerState()
{

}

void PlayerState::change(const char* name)
{
	char key[40] = { 0 };
	sprintf_s(key, "%s%s", GetStringData("PlayerType").c_str(), name);
	Animation* animation = AnimationCache::getInstance()->getAnimation(key);
	Animate* animate = Animate::create(animation);
	m_playerFace->stopAllActions();
	m_playerFace->runAction(RepeatForever::create(animate));
}