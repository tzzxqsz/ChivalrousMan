#pragma once
#ifndef __NET_WORK_MANAGER_H__
#define __NET_WORK_MANAGER_H__
#include"PreProcess.h"
#include"Signal.h"

using NetMsg = std::map<std::string, std::string>;

class NetWorkManager 
{
	GET_SINGLE_OBJECT(NetWorkManager)
public:
	NetWorkManager(const NetWorkManager&) = delete;
	NetWorkManager& operator=(const NetWorkManager&) = delete;

	Slot* add(const int& messageId, const EventHandler& evHandler);

	Slot* add(const int& messageId, const std::function<void(Json::Value&)>&);
	
	void dispatch(const int& messageId,Json::Value& message);

	void send(const int& messageId, const std::map<std::string, std::string>& msg);
private:
	NetWorkManager() {}
	~NetWorkManager() {}
	std::map<int, Signal> m_signals;

	SINGLE_ATTRIBUTES(NetWorkManager);
};

#endif // !__NET_WORK_MANAGER_H__

