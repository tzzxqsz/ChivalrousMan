#include"Event.h"
using namespace Json;

long long int Slot::count = 0;

Slot::Slot(SlotListener* listener,const EventHandler& evh,const bool& once)
{
	this->flag = false;
	this->listener = listener;
	this->evh = evh;
	this->once = once;
	this->id = count++;
}

Slot::Slot(SlotListener* listener, const std::function<void(Json::Value&)>& func, const bool& once) {
	this->listener = listener;
	flag = true;
	this->func = func;
	this->once = once;
	this->id = count++;
}

void Slot::dispatch(Json::Value& message)
{
	if (flag)
		func(message);
	else
		(evh.handler->*evh.func)(message);
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


EventHandler handler(cocos2d::CCObject* CCObject,SEL_EventFunc func)
{
	EventHandler evh;
	evh.handler = CCObject;
	evh.func = func;
	return evh;
}