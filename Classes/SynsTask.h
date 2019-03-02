#pragma once
#ifndef __SYNS_TASK_H__
#define __SYNS_TASK_H__
#include"PreProcess.h"
#include<thread>
#include<functional>

/*
*“Ï≤Ω»ŒŒÒ
*/
class SynsTask
{
public:
	SynsTask(std::function<void(void)> func);
private:
	
};

#endif // !__SYNS_TASK_H_

