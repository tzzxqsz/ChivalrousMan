#include"Signal.h"
#include"jsonCpp/reader.h"
#include"jsonCpp/value.h"

Signal::Signal()
{
}

Signal::~Signal()
{
	for (auto var : m_slots)
	{
		delete var;
		var = nullptr;
	}
}

void Signal::removeSlot(const long long int & slotId)
{
	for (auto var : m_slots)
	{
		if (var->getId() == slotId)
		{
			m_slots.remove(var);
			delete var;
			var = nullptr;
		}
	}
}

Slot * Signal::add(const EventHandler & handler)
{
	Slot* slot = new Slot(this, handler);
	m_slots.push_back(slot);
	return slot;
}

Slot * Signal::addOnce(const EventHandler & handler)
{
	Slot* slot = new Slot(this, handler, true);
	m_slots.push_back(slot);
	return slot;
}

Slot * Signal::add(const std::function<void(Json::Value&)>& func)
{
	Slot* slot = new Slot(this, func);
	m_slots.push_back(slot);
	return slot;
}

Slot * Signal::addOnce(const std::function<void(Json::Value&)>& func)
{
	Slot* slot = new Slot(this, func, true);
	m_slots.push_back(slot);
	return slot;
}

void Signal::dispatch(Json::Value& message)
{
	for (auto var : m_slots)
	{
		var->dispatch(message);
	}
}
