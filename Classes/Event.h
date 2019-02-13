#pragma once
/*
*事件槽一个事件一个槽
*/
#ifndef __EVENT_H__
#define __EVENT_H__
#include"PreProcess.h"
#include"SlotListener.h"
#include<iostream>
#include<functional>

#define SEL_EVENTFUNC(func) static<cocos2d::Ref::*SEL_EventFunc>(&func)
 
typedef void (cocos2d::Ref::*SEL_EventFunc)(void*);

typedef struct _Event{
	cocos2d::Ref* handler;
	void* param;
	SEL_EventFunc func;
}EventHandler;

 class Slot
 {
 public:
	 Slot(SlotListener* listener, const EventHandler& evh, const bool& once = false);

	 Slot(SlotListener* listener,const std::function<void(void)>& func, const bool& once = false);

	 virtual ~Slot() {}

	 virtual void dispatch();

	 bool operator==(const Slot& slot);

	 long long int getId() const;

	 void remove();
 private:
	 long long int id;
	 bool flag = 0;
	 EventHandler evh;
	 std::function<void(void)> func;
	 bool once;
	 SlotListener* listener;
	 
	 static long long int count;
 };

 EventHandler Handler(cocos2d::Ref* ref, SEL_EventFunc func, void* param = nullptr);

#endif // !__EVENT_H__
