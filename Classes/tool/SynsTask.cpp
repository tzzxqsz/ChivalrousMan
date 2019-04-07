#include"SynsTask.h"

SynsTask::SynsTask(std::function<void(void)> func)
{
	std::thread thread([func] {
		func();
	});
	thread.detach();
}
