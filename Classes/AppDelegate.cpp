#include"AppDelegate.h"
#include"start/BeginScene.h"
#include"tool/GameData.h"
#include"tool/GameDynamicData.h"
#include"map/MapInfo.h"
#include"player/CameraPlayer.h"
#include"tool/Commen.h"
#include"tool/AudioSystem.h"
#include"tool/ReflectNpc.h"
#include"net/SocketManager.h"
#include"equipment/EquipmentManager.h"
#include"skill/SkillManager.h"
#include"backpack/BackPackManager.h"
#include"team/TeamManager.h"
#include"task/TaskLayer.h"
#include"talk/TalkManager.h"
#include"player/PlayerManager.h"
#include"fight/FightManager.h"
#include"friend/FriendManager.h"
#include"skillitem/RealSkill.h"
#include"common/MaxTopLayer.h"

#define _IS_EDITER_ 0

#define LoadPlayerAnimation(player)    \
{      \
	char name[40] = { 0 };    \
sprintf_s(name, "%sWaitLeft", player);    \
LoadAnimationFromFile(StringValue(name).c_str(), name, 1, FloatValue("PlayerFps"));  \
sprintf_s(name, "%sWaitRight", player);    \
LoadAnimationFromFile(StringValue(name).c_str(), name, 1, FloatValue("PlayerFps"));  \
sprintf_s(name, "%sWaitDown", player);    \
LoadAnimationFromFile(StringValue(name).c_str(), name, 1, FloatValue("PlayerFps")); \
sprintf_s(name, "%sWaitUp", player);   \
LoadAnimationFromFile(StringValue(name).c_str(), name, 1, FloatValue("PlayerFps"));  \
sprintf_s(name, "%sRunLeft",  player);   \
LoadAnimationFromFile(StringValue(name).c_str(), name, 12, FloatValue("PlayerFps"));  \
sprintf_s(name, "%sRunRight",  player);   \
LoadAnimationFromFile(StringValue(name).c_str(), name, 12, FloatValue("PlayerFps"));  \
sprintf_s(name, "%sRunDown",  player);   \
LoadAnimationFromFile(StringValue(name).c_str(), name, 12, FloatValue("PlayerFps"));  \
sprintf_s(name, "%sRunUp",  player);   \
LoadAnimationFromFile(StringValue(name).c_str(), name, 12, FloatValue("PlayerFps"));  \
}

AppDelegate::AppDelegate()
{
	
}

AppDelegate::~AppDelegate() 
{
	CameraPlayer::release();
	HelpToolSystem::releaseAudioSystem();
	MapInfo::release();
	ReflectNpc::release();
	SocketManager::release();
	EquipmentManager::realse();
	SkillManager::release();
	BackPackManager::release();
	GameData::release();
	GameDynamicData::release();
	TeamManager::release();
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
	if (!glview) {
#if _IS_EDITER_==1
		glview = GLViewImpl::createWithRect("ChivalrousMan", Rect(0, 0, 1680, 960));
		director->setOpenGLView(glview);
	}
	director->getOpenGLView()->setDesignResolutionSize(1680, 960, ResolutionPolicy::SHOW_ALL);
#else
		glview = GLViewImpl::createWithRect("ChivalrousMan", Rect(0, 0, 960, 640));
		director->setOpenGLView(glview);
	}
	director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::SHOW_ALL);
#endif // _IS_EDITER_==0
   

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

    // create a scene. it's an autorelease object
	SocketManager::getInstance();
	instanceManager();
	registerReflectClass();
	LoadResource();
	HelpToolSystem::getInstance();
	auto scene = BeginScene::create();
	director->runWithScene(scene);
	MaxTopLayer::attach();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
     //SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::LoadResource()
{
	Animation *Player1Ani = Animation::create();
	char filename[40] = { 0 };
	Player1Ani->setDelayPerUnit(FloatValue("PlayerFps"));
	for (int i = 1; i <= 8; ++i)
	{
		sprintf_s(filename, "player1/2_%d.png", i);
		Texture2D *texture = TextureCache::getInstance()->addImage(filename);
		Rect rect{ 0,0,texture->getContentSize().width,texture->getContentSize().height };
		Player1Ani->addSpriteFrameWithTexture(texture, rect);
	}
	AnimationCache::getInstance()->addAnimation(Player1Ani, "Player1");

	LoadPlayerAnimation("Player1");
	LoadPlayerAnimation("Player2");
	LoadPlayerAnimation("Player3");

	Animation* doorAnimation;
	LoadAnimationFromMinFile("door/door", 11, 0.1, doorAnimation);
	AnimationCache::getInstance()->addAnimation(doorAnimation, "DoorAnimation");
	LoadSkillAnimation();
}

void AppDelegate::LoadAnimationFromFile(const char* filename,char* key,int num,float delay) 
{
	auto outAni = Animation::create();
	Texture2D* texture = TextureCache::getInstance()->addImage(filename);
	float h = texture->getContentSize().height;
	float w = texture->getContentSize().width / num;
	outAni->setDelayPerUnit(delay);
	for (int i = 0; i < num; ++i)
	{
		SpriteFrame* frame = SpriteFrame::createWithTexture(texture, Rect{ i*w,0,w,h });
		outAni->addSpriteFrame(frame);
	}
	AnimationCache::getInstance()->addAnimation(outAni, key);
}

void AppDelegate::registerReflectClass()
{
	REG_REFLECT_CLASS(NpcBlue);
	REG_REFLECT_CLASS(NpcEquip);
	REG_REFLECT_CLASS(NpcMamom);
	REG_REFLECT_CLASS(NpcMonk);
	REG_REFLECT_CLASS(NpcPink);
	REG_REFLECT_CLASS(NpcSkill);
	REG_REFLECT_CLASS(NpcVallige);
}

void AppDelegate::LoadSkillAnimation()
{
	std::string skill[] = { "CrackIt","Dante","DragonRoar","LightStrike",
		"Long","RecallCountermand","SealOfTheBlade","XBArrow" };
	int nums[] = { 16,14,9,9,10,17,15,9 };
	for (int i = 0; i < 8; ++i)
	{
		RealSkill::loadAnimation(StringValue(skill[i]) + skill[i], nums[i], 0.15);
	}
}

void AppDelegate::instanceManager()
{
	PlayerManager::getInstance();
	TalkManager::getInstance();
	TeamManager::getInstance();
	FightManager::getInstance();
	FriendManager::getInstance();
}
