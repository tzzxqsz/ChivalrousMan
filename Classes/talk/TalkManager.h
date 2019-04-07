#pragma once
#ifndef __TALK_MANAGER_H__
#define __TALK_MANAGER_H__
#include"tool/PreProcess.h"
#include"jsonCpp/value.h"

struct TalkMsg
{
	std::string rolename;    //˭���͵�
	std::string destname;   //����˭
	std::string msg;             //��Ϣ����
	bool change = false;
};

class TalkManager :public cocos2d::CCObject
{
	GET_SINGLE_OBJECT(TalkManager)
public:
	void c2sWorkTalk(const std::string& content);

	void c2sPrivateTalk(const std::string& content, const int& dest);

	void s2cWorkTalk(Json::Value& msg);

	void s2cPrivateTalk(Json::Value& msg);

	void removePrivateMsg(const int&);

	std::map<int, std::deque<TalkMsg>>& getPrivateMsgs() { return m_privateTalkMsgs; }
private:
	TalkManager();
	~TalkManager();

	std::deque<TalkMsg> m_worldTalkMsgs;    //����������Ϣ
	std::map<int, std::deque<TalkMsg>> m_privateTalkMsgs;    //˽����Ϣ

	SINGLE_ATTRIBUTES(TalkManager);
};

#endif // !__TALK_MANAGER_H__

