#include"TalkManager.h"
#include"tool/GameData.h"
#include"tool/GameDynamicData.h"
#include"player/PlayerManager.h"
#include"main/GameUILayer.h"
#include"PrivateTalkLayer.h"
#include"net/NetWorkManager.h"
#include"net/MessageConst.h"

DEFINE_SINGLE_ATTRIBUTES(TalkManager);

TalkManager::TalkManager()
{
	NetWorkManager::getInstance()->add(MESSAGE_WORLD_TALK, handler(this, SEL_EVENTFUNC(TalkManager::s2cWorkTalk)));
	NetWorkManager::getInstance()->add(MESSAGE_PRIVATE_TALK, handler(this, SEL_EVENTFUNC(TalkManager::s2cPrivateTalk)));
}

TalkManager::~TalkManager()
{
}
void TalkManager::c2sWorkTalk(const std::string& content)
{
	NetMsg msg;
	msg["fd"] = -1;
	msg["msg"] = content;
	NetWorkManager::getInstance()->send(MESSAGE_WORLD_TALK, msg);
}

void TalkManager::c2sPrivateTalk(const std::string & content, const int & dest)
{
	NetMsg msg;
	msg["fd"] =-1;
	msg["dest"] = dest;
	msg["msg"] = content;
	NetWorkManager::getInstance()->send(MESSAGE_PRIVATE_TALK, msg);
}

void TalkManager::s2cWorkTalk(Json::Value & msg)
{
	TalkMsg tmsg;
	int fd = msg["fd"].asInt();
	if (fd != -1)
		tmsg.rolename = PlayerManager::getInstance()->findRoleNameByFd(fd);
	else
		tmsg.rolename = StringValue("Me");
	tmsg.msg = msg["msg"].asString();
	m_worldTalkMsgs.push_back(tmsg);
	if (m_worldTalkMsgs.size() > 100)
	{
		m_worldTalkMsgs.pop_front();
	}
	auto gameUILayer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameUILayer");
	if (gameUILayer)
	{
		dynamic_cast<GameUILayer*>(gameUILayer)->updateWorldTalkQueue(tmsg);
	}
}

void TalkManager::s2cPrivateTalk(Json::Value & msg)
{
	TalkMsg tmsg;
	int realfd;
	int fd = msg["fd"].asInt();
	if (fd != -1)
	{
		tmsg.rolename = PlayerManager::getInstance()->findRoleNameByFd(fd);
		realfd = fd;
	}
	else
	{
		tmsg.rolename = StringValue("Me");
		realfd = msg["dest"].asInt();
	}
	tmsg.destname = PlayerManager::getInstance()->findRoleNameByFd(realfd);
	if (tmsg.destname == "")
	{
		SetIntData("IsHaveTip", 1);
		SetStringData("TipText", StringValue("OffLine"));
		return;
	}
	tmsg.msg = msg["msg"].asString();
	if (m_privateTalkMsgs.find(realfd) != m_privateTalkMsgs.end())
	{
		if (m_privateTalkMsgs.size() >= 6)
			m_privateTalkMsgs.erase(m_privateTalkMsgs.begin());
	}
	m_privateTalkMsgs[realfd].push_back(tmsg);

	auto ptlayer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("PrivateTalkLayer");
	if (ptlayer != nullptr)
		dynamic_cast<PrivateTalkLayer*>(ptlayer)->addMsg(tmsg.rolename, tmsg.msg);

	if (fd != -1)
	{
		m_privateTalkMsgs[realfd][0].change = true;
		auto gameUILayer = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("GameUILayer");
		if (gameUILayer != nullptr)
			dynamic_cast<GameUILayer*>(gameUILayer)->setRedSpot(true);
	}
	if (m_privateTalkMsgs[realfd].size() >18)
	{
		m_privateTalkMsgs[realfd].pop_front();
	}
}

void TalkManager::removePrivateMsg(const int & fd)
{
	m_privateTalkMsgs.erase(fd);
}


