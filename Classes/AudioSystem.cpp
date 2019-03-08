#include"AudioSystem.h"
#include"Commen.h"
#include"GameData.h"
#include"GameDynamicData.h"
#include"SimpleAudioEngine.h"
#include"TeamManager.h"
#include"CameraPlayer.h"
#include"SocketManager.h"
#include"PlayerManager.h"
#include"TeamManager.h"
#include"MapInfo.h"

using namespace CocosDenshion;
using namespace std;

DEFINE_SINGLE_ATTRIBUTES(HelpToolSystem);

HelpToolSystem::HelpToolSystem():
	m_exitThread(false)
{
	m_threadHandle = new std::thread{ &HelpToolSystem::WorkThread,this };
}

HelpToolSystem::~HelpToolSystem()
{
	m_exitThread = true;
	if (m_threadHandle != nullptr)
		m_threadHandle->join();
	RELEASE_NULL(m_threadHandle);
}

void HelpToolSystem::WorkThread()
{
	long count = 0;
	long count2 = 0;
	while (true)
	{
		if (m_exitThread)
		{
			break;
		}
		
		CheckBgMusic();
		Sleep(50);
		count++;
		count2++;
		if (count >= 1800 && GetIntData("IsHaveGameScene") == 1)
		{
			PlayerManager::getInstance()->c2sVerifyPlayerPos();
			count = 0;
		}
	}
}

void HelpToolSystem::CheckBgMusic()
{
	if (GetIntData("BgMusic") == 1)
	{
		if (!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
			SimpleAudioEngine::getInstance()->playBackgroundMusic(StringValue("BgMusic").c_str(), true);
	}
	else
	{
		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
}

void HelpToolSystem::releaseAudioSystem()
{
	RELEASE_NULL(m_instance);
}