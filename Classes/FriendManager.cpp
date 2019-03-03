#include"FriendManager.h"
#include"DBDao.h"
#include"Model.h"
#include"NetWorkManager.h"
#include"PlayerManager.h"
#include"MessageConst.h"


DEFINE_SINGLE_ATTRIBUTES(FriendManager);

FriendManager::FriendManager()
{
	NetWorkManager::getInstance()->add(MESSAGE_APPLY_FRIEND, handler(this, SEL_EVENTFUNC(FriendManager::s2cApplyFriend)));
	
}

FriendManager::~FriendManager()
{
}

void FriendManager::c2sApplyFriend(const std::string& rolename)
{
	NetMsg msg;
	msg["fd"] = -1;
	msg["rolename"] = rolename;
	NetWorkManager::getInstance()->send(MESSAGE_APPLY_FRIEND, msg);
}

void FriendManager::s2cApplyFriend(Json::Value & msg)
{
	Player_Info info;
	info.playername = msg["playername"].asString();
	info.playertype = msg["playertype"].asString();
	info.rolename = msg["rolename"].asString();
	info.grade = msg["grade"].asInt();
	m_applyList.push_back(info);
}

std::vector<Player_Info>& FriendManager::getFriendList(const bool& refresh)
{
	if (refresh)
	{
		DBDao<Friend> db;
		auto list = db.queryModel();
		m_friendList.clear();
		for (auto var : list)
		{
			Player_Info info;
			info.playername = var.getfriendpname();
			info.rolename = var.getfriendrname();
			info.playertype = var.getfriendrtype();
			info.grade = std::stoi(var.getfriendgrade());
			m_friendList.push_back(info);
		}
	}
	return m_friendList;
}

std::vector<Player_Info> FriendManager::getAddFriendList()
{
	DBDao<PlayerInfo> db;
	auto pList = db.queryModel();
	std::vector<Player_Info> retList;
	for (auto var : pList)
	{
		Player_Info info;
		info.playername = var.getplayerName();
		info.rolename = var.getroleName();
		info.playertype = var.getroleType();
		info.grade = std::stoi(var.getgrade());
		if (!IsFriend(info))
			retList.push_back(info);
	}
	int size = retList.size();
	if (size > 20)
	{
		int morecount = size - 20;
		std::random_shuffle(retList.begin(), retList.end(), RandomGenerator());
		for (int i = 1; i <= morecount; ++i)
		{
			retList.pop_back();
		}
	}
	return retList;
}

std::vector<Player_Info> FriendManager::getApplyFriendList()
{
	return m_applyList;
}

bool FriendManager::IsFriend(const Player_Info & info)
{
	for (auto var : m_friendList)
	{
		if (info.rolename == var.rolename)
		{
			return true;
		}
	}
	return false;
}
