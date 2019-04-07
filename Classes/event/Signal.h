#pragma once
/**
*事件实例管理一类事件
*/
#ifndef __SIGNAL_H__
#define  __SIGNAL_H__
#include"Event.h"
#include<list>

class Signal:public SlotListener
{
public:
	Signal();
	virtual ~Signal();

	virtual void removeSlot(const long long int& slotId);

	Slot* add(const EventHandler& handler);

	Slot* addOnce(const EventHandler& handler);

	Slot* add(const std::function<void(Json::Value&)>&);

	Slot* addOnce(const std::function<void(Json::Value&)>& func);

	void dispatch(Json::Value & message);
private:
	std::list<Slot*> m_slots;
};

#endif // !__SIGNAL_H__

