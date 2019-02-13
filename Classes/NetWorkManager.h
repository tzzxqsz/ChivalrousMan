#pragma once
#ifndef __NET_WORK_MANAGER_H__
#define __NET_WORK_MANAGER_H__
#include"PreProcess.h"
#include"Signal.h"
#include"cHash_Map.h"

class NetWorkManager 
{
	GET_SINGLE_OBJECT(NetWorkManager)
public:
	NetWorkManager(const NetWorkManager&) = delete;
	NetWorkManager& operator=(const NetWorkManager&) = delete;

	void add(const int& messageId);
	
	void dispatch(const int& messageId);
private:
	NetWorkManager() {}
	~NetWorkManager() {}
	cHash_Map<int, Signal> m_signals;

	SINGLE_ATTRIBUTES(NetWorkManager);
};

#endif // !__NET_WORK_MANAGER_H__

