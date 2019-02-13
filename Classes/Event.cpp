#include"Event.h"

long long int Slot::count = 0;

Slot::Slot(SlotListener* listener,const EventHandler& evh,const bool& once)
{
	this->listener = listener;
	this->evh = evh;
	this->once = once;
	this->id = count++;
}

Slot::Slot(SlotListener* listener, const std::function<void(void)>& func, const bool& once) {
	this->listener = listener;
	flag = true;
	this->func = func;
	this->once = once;
	this->id = count++;
}

void Slot::dispatch()
{
	if (flag)
		func();
	else
		(evh.handler->*evh.func)(evh.param);
	if (once)
		this->remove();
}

bool Slot::operator==(const Slot & slot)
{
	return this->id == slot.id;
}

long long int Slot::getId() const
{
	return this->id;
}

void Slot::remove()
{
	this->listener->removeSlot(this->getId());
}


EventHandler Handler(cocos2d::Ref* ref,SEL_EventFunc func,void* param)
{
	EventHandler evh;
	evh.handler = ref;
	evh.func = func;
	evh.param = param;
	return evh;
}