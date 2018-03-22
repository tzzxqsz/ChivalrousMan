#include"FriendManager.h"
#include"Commen.h"
#include"DBDao.h"
#include"Model.h"

int FriendManager::addFriend(const GameFriend& fr)
{
	for (auto var : m_friendlist)
	{
		if (var == fr)
		{
			return;
		}
	}
	m_friendlist.push_back(fr);
}

int FriendManager::delFrinend(const GameFriend& fr)
{
	for (auto it = m_friendlist.begin(); it != m_friendlist.end(); ++it)
	{
		if ((*it) == fr)
		{
			m_friendlist.erase(it);
			return 0;
		}
	}
	return -1;
}