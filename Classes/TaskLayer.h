#pragma once
#ifndef __TASK_LAYER_H__
#define __TASK_LAYER_H__
#include"PreProcess.h"
#include"CommonTouchLayer.h"
#include<list>

class TaskItem;

/*
*class TaskLayer
*任务面板层
*/
class TaskLayer Inherit(CommonTouchLayer)
{
	CLASS_ESSENTAIL(TaskLayer)
	CREATE_FUNC(TaskLayer)
public:
	bool init() override;

	/*
	*移除任务面板上的人物item
	*@param item：需要移除的item
	*/
	void removeTaskItem(TaskItem* item);
private:
	/*
	*初始化任务面板上的任务列表
	*/
	void initTaskItem(cocos2d::Vec2 basePos);

	std::list<TaskItem*> m_itemlist;
};

#endif // !__TASK_LAYER_H__

