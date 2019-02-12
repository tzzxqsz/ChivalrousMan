#pragma once
#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__
#include"Event.h"
#include<map>
#include<list>

class EventManager
{
	GET_SINGLE_OBJECT(EventManager)
public:

	const Slot& AddEvent(const Event& e, Slot& slot, bool once);

	void Dispatch(const Event& e);

	void Remove(const Slot& slot);
private:
	EventManager() {}
	~EventManager() {}

	std::map<Event, std::list<Slot>> m_slotMaps;

	SINGLE_ATTRIBUTES(EventManager);
};

#endif // !

