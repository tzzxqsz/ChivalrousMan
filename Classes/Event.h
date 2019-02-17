#pragma once
/*
*事件槽一个事件一个槽
*/
#ifndef __EVENT_H__
#define __EVENT_H__
#include"PreProcess.h"
#include"SlotListener.h"
#include"jsonCpp/reader.h"
#include"jsonCpp/value.h"
#include<iostream>
#include<functional>

#define SEL_EVENTFUNC(func) static_cast<SEL_EventFunc>(&func)
 
typedef void (cocos2d::CCObject::*SEL_EventFunc)(Json::Value&);

typedef struct _Event{
	cocos2d::CCObject* handler;
	SEL_EventFunc func;
}EventHandler;

 class Slot
 {
 public:
	 Slot(SlotListener* listener, const EventHandler& evh, const bool& once = false);

	 Slot(SlotListener* listener,const std::function<void(Json::Value&)>& func, const bool& once = false);

	 virtual ~Slot() {}

	 virtual void dispatch(Json::Value& message);

	 bool operator==(const Slot& slot);

	 long long int getId() const;

	 void remove();
 private:
	 long long int id;
	 bool flag = 0;
	 EventHandler evh;
	 std::function<void(Json::Value&)> func;
	 bool once;
	 SlotListener* listener;
	 
	 static long long int count;
 };

 EventHandler handler(cocos2d::CCObject* CCObject, SEL_EventFunc func);

#endif // !__EVENT_H__
