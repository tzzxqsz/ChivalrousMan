#pragma once
#ifndef __SLOT_LISTENER_H__

class SlotListener
{
public:
	SlotListener() {}
	virtual ~SlotListener() {}
	
	virtual void removeSlot(const long long int& slotId) = 0;
};

#endif // !__SLOT_LISTENER_H__

