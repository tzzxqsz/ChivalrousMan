#pragma once
#ifndef __EVENT_H__
#define __EVENT_H__
#include"PreProcess.h"
#include<iostream>
#include<functional>

#define SEL_EVENTFUNC(func) static<cocos2d::Ref::*SEL_EventFunc>(&func)
 
typedef void (cocos2d::Ref::*SEL_EventFunc)(void*);

typedef struct _Event{
	cocos2d::Ref* handler;
	void* param;
	SEL_EventFunc func;
}EventHandler;

 enum class Event
{
	 
};

 class Slot
 {
 public:
	 Slot(EventHandler evh, bool once = false);

	 Slot(std::function<void(void)> func, bool once = false);

	 ~Slot() {}

	 void Dispatch();

	 bool operator==(const Slot& slot);

	 void Remove();

	 long long int GetId() const;
 private:
	 long long int id;
	 bool flag = 0;
	 EventHandler evh;
	 std::function<void(void)> func;
	 bool once;
	 
	 static long long int count;
 };

 Slot Handler(EventHandler);

 Slot Handler(std::function<void(void)>);

#endif // !__EVENT_H__
