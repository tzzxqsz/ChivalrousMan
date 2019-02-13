#include"Signal.h"

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
	for (auto it = m_slots.begin(); it != m_slots.end(); ++it)
	{
		if ((*it)->getId() == slotId)
		{
			m_slots.erase(it);
			return;
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

Slot * Signal::add(const std::function<void(void)>& func)
{
	Slot* slot = new Slot(this, func);
	m_slots.push_back(slot);
	return slot;
}

Slot * Signal::addOnce(const std::function<void(void)>& func)
{
	Slot* slot = new Slot(this, func, true);
	m_slots.push_back(slot);
	return slot;
}

void Signal::dispatch()
{
	for (auto var : m_slots)
	{
		var->dispatch();
	}
}
