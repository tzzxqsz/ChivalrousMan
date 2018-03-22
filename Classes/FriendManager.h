#pragma once
#ifndef __FRIEND_MAMAGER_H__
#define __FRIEND_MAMAGER_H__
#include"PreProcess.h"
#include<string>
#include<list>

//������Ϣ
struct GameFriend
{
	std::string playername;
	std::string rolename;
	
	bool operator==(const GameFriend& fr)
	{
		this->playername == fr.playername&&this->rolename == fr.rolename;
	}
};

/*
*class FriendManager
*��Һ��ѹ���
*/
class FriendManager
{
	CLASS_ESSENTAIL(FriendManager);
	GET_SINGLE_OBJECT(FriendManager);
public:
	/*
	* getFriendList()
	*��ȡ������Ϣ�б�
	*/
	std::list<GameFriend>& getFriendList() { return m_friendlist; }

	/*
	*addFriend(GameFriend fr);
	*�������
	*@param fr:������Ϣ
	*@return int:����-1��ʾ���ʧ�ܣ�����0��ʾ��ӳɹ�
	*/
	int addFriend(const GameFriend& fr);

	/*
	*delFrinend(const GameFriend& fr)
	*ɾ������
	*@param fr:������Ϣ
	*@return int������-1��ʾɾ��ʧ�ܣ�����0��ʾɾ���ɹ�
	*/
	int delFrinend(const GameFriend& fr);
private:
	std::list<GameFriend> m_friendlist;

	SINGLE_ATTRIBUTES(FriendManager);
};

#endif // !__FRIEND_MAMAGER_H__

