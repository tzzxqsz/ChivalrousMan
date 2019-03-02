#pragma once
#ifndef __SINGAL_MANAGER_H__
#define __SINGAL_MANAGER_H__
#include"PreProcess.h"
#include"Signal.h"

class SignalManager
{
	GET_SINGLE_OBJECT(SignalManager)
public:
	Slot* add(const int& messageId, const EventHandler& evHandler, const bool& once = false);

	Slot* add(const int& messageId, const std::function<void(Json::Value&)>&, const bool& once = false);

	void dispatch(const int& messageId, Json::Value& message = Json::Value());
private:
	SignalManager();
	~SignalManager();

	std::map<int, Signal> m_signals;

	SINGLE_ATTRIBUTES(SignalManager);
};

#endif // !__SINGAL_MANAGER_H__

