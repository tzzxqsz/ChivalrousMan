#include"Event.h"
#include"EventManager.h"

long long int Slot::count = 0;

Slot::Slot(EventHandler evh,bool once) {
	this->evh = evh;
	this->id = count++;
	this->once;
}

Slot::Slot(std::function<void(void)> func,bool once) {
	flag = true;
	this->func = func;
	this->id = count++;
	this->once = once;
}

void Slot::Dispatch()
{
	if (flag)
		func();
	else
		(evh.handler->*evh.func)(evh.param);
	if (once)
		this->Remove();
}

bool Slot::operator==(const Slot & slot)
{
	return this->id == slot.id;
}

void Slot::Remove()
{
	EventManager::getInstance()->Remove(*this);
}

long long int Slot::GetId() const
{
	return this->id;
}


Slot Handler(cocos2d::Ref* ref,SEL_EventFunc func,void* param)
{
	EventHandler evh;
	evh.handler = ref;
	evh.func = func;
	evh.param = param;
	return Slot(evh);
}

Slot Handler(std::function<void(void)> func)
{
	return Slot(func);
}