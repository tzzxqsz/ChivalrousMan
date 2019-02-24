#pragma once
#ifndef __TASK_LAYER_H__
#define __TASK_LAYER_H__
#include"PreProcess.h"
#include"CommonTouchLayer.h"
#include<list>

class TaskItem;

/*
*class TaskLayer
*��������
*/
class TaskLayer Inherit(CommonTouchLayer)
{
	CLASS_ESSENTAIL(TaskLayer)
	CREATE_FUNC(TaskLayer)
public:
	bool init() override;

	/*
	*�Ƴ���������ϵ�����item
	*@param item����Ҫ�Ƴ���item
	*/
	void removeTaskItem(TaskItem* item);
private:
	/*
	*��ʼ����������ϵ������б�
	*/
	void initTaskItem(cocos2d::Vec2 basePos);

	std::list<TaskItem*> m_itemlist;
};

#endif // !__TASK_LAYER_H__

