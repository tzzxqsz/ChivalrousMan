#include"FriendManager.h"
#include"DBDao.h"
#include"Model.h"
#include"NetWorkManager.h"
#include"PlayerManager.h"
#include"MessageConst.h"
#include"GameData.h"
#include"GameDynamicData.h"
#include"SignalManager.h"
#include"CameraPlayer.h"


DEFINE_SINGLE_ATTRIBUTES(FriendManager);

FriendManager::FriendManager()
{
	NetWorkManager::getInstance()->add(MESSAGE_APPLY_FRIEND, handler(this, SEL_EVENTFUNC(FriendManager::s2cApplyFriend)));
	NetWorkManager::getInstance()->add(MESSAGE_AGREE_FRIEND, handler(this, SEL_EVENTFUNC(FriendManager::s2cAgreeFriend)));
	NetWorkManager::getInstance()->add(MESSAGE_REJECT_FRIEND, handler(this, SEL_EVENTFUNC(FriendManager::s2cRejectFriend)));
	NetWorkManager::getInstance()->add(MESSAGE_DEL_FRIEND, handler(this, SEL_EVENTFUNC(FriendManager::s2cDelFriend)));
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

void FriendManager::c2sAgreeFriend(const Player_Info& info)
{
	DBDao<Friend> db;
	Friend fd;
	fd.setplayername(GetStringData("playername"));
	fd.setrolename(GetStringData("rolename"));
	fd.setfriendrtype(info.playertype);
	fd.setfriendrname(info.rolename);
	fd.setfriendpname(info.playername);
	fd.setfriendgrade(NTS(info.grade));
	db.setModel(fd);
	db.insertModel();
	db.close();
	DBDao<Friend> db1;
	fd.setplayername(info.playername);
	fd.setrolename(info.rolename);
	fd.setfriendrtype(info.playertype);
	fd.setfriendrname(GetStringData("rolename"));
	fd.setfriendpname(GetStringData("playername"));
	fd.setfriendgrade(NTS(CameraPlayer::getPlayerInstance()->getPlayerData().getgrade()));
	db1.setModel(fd);
	db1.insertModel();
	db1.close();

	NetMsg msg;
	msg["rolename"] = info.rolename;
	NetWorkManager::getInstance()->send(MESSAGE_AGREE_FRIEND, msg);
	removeApplyFriendList(info.rolename);
	getFriendList(true);
}

void FriendManager::c2sRejectFriend(const std::string & rolename)
{
	NetMsg msg;
	msg["rolename"] = rolename;
	NetWorkManager::getInstance()->send(MESSAGE_REJECT_FRIEND, msg);
	removeApplyFriendList(rolename);
}

void FriendManager::c2sDelFriend(const Player_Info& info)
{
	DBDao<Friend> db;
	Friend fd;
	fd.setplayername(GetStringData("playername"));
	fd.setrolename(GetStringData("rolename"));
	fd.setfriendpname(info.playername);
	fd.setfriendrname(info.rolename);
	db.setModel(fd);
	db.deleteModel();
	db.close();
	DBDao<Friend> db1;
	fd.setplayername(info.playername);
	fd.setrolename(info.rolename);
	fd.setfriendpname(GetStringData("playername"));
	fd.setfriendrname(GetStringData("rolename"));
	db1.setModel(fd);
	db1.deleteModel();
	db1.close();

	NetMsg msg;
	msg["rolename"] = info.rolename;
	NetWorkManager::getInstance()->send(MESSAGE_DEL_FRIEND, msg);
	getFriendList(true);
}

void FriendManager::s2cApplyFriend(Json::Value & msg)
{
	Player_Info info;
	info.playername = msg["playername"].asString();
	info.playertype = msg["playertype"].asString();
	info.rolename = msg["rolename"].asString();
	info.grade = msg["grade"].asInt();
	if (!isExitsApply(info))
		m_applyList.push_back(info);
}

void FriendManager::s2cAgreeFriend(Json::Value & msg)
{
	getFriendList(true);
}

void FriendManager::s2cRejectFriend(Json::Value & msg)
{
	
}

void FriendManager::s2cDelFriend(Json::Value & msg)
{
	getFriendList(true);
}

std::vector<Player_Info>& FriendManager::getFriendList(const bool& refresh)
{
	if (refresh)
	{
		DBDao<Friend> db;
		Friend fd;
		fd.setplayername(GetStringData("playername"));
		fd.setrolename(GetStringData("rolename"));
		db.setModel(fd);
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
		if (!isFriend(info))
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

void FriendManager::removeApplyFriendList(const std::string& rolename)
{
	for (auto it = m_applyList.begin(); it != m_applyList.end();)
	{
		if (it->rolename == rolename)
		{
			it = m_applyList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

bool FriendManager::isFriend(const Player_Info & info)
{
	if (info.rolename == GetStringData("rolename"))
		return true;
	for (auto var : m_friendList)
	{
		if (info.rolename == var.rolename)
		{
			return true;
		}
	}
	return false;
}

bool FriendManager::isExitsApply(const Player_Info & info)
{
	for (auto it = m_applyList.begin(); it != m_applyList.end(); ++it)
	{
		if (it->rolename == info.rolename)
		{
			return true;
		}
	}
	return false;
}
