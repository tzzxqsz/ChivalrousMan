#pragma once
#ifndef __SYNS_TASK_H__
#define __SYNS_TASK_H__
#include"PreProcess.h"
#include<thread>
#include<functional>

/*
*�첽����
*/
class SynsTask
{
public:
	SynsTask(std::function<void(void)> func);
private:
	
};

#endif // !__SYNS_TASK_H_

