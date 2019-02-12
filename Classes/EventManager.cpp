#include"EventManager.h"

DEFINE_SINGLE_ATTRIBUTES(EventManager);

const Slot&  EventManager::AddEvent(const Event& e, Slot& slot,bool once)
{
	if (m_slotMaps.find(e) != m_slotMaps.end())
	{
		m_slotMaps[e].push_back(slot);
	}
	else
	{
		std::list<Slot> list;
		list.push_back(slot);
		m_slotMaps[e] = list;
	}
	return slot;
}

void EventManager::Dispatch(const Event& e)
{
	for (auto& var : m_slotMaps[e])
	{
		var.Dispatch();
	}
}

void EventManager::Remove(const Slot & slot)
{
	for (auto itMap = m_slotMaps.begin(); itMap != m_slotMaps.end(); ++itMap)
	{
		for (auto it = itMap->second.begin(); it != itMap->second.end(); ++it)
		{
			if (it->GetId() == slot.GetId())
			{
				itMap->second.erase(it);
				if (itMap->second.empty())
				{
					m_slotMaps.erase(itMap);
				}
				return;
			}
		}
	}
}
