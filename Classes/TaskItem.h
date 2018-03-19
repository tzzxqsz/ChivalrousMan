#pragma once
#ifndef __TASK_ITEM_H__
#define __TASK_ITEM_H__
#include"PreProcess.h"
#include"TaskSystem.h"

/*
*class TaskItem
*用于在任务面板显示任务详情的item
*/
class TaskItem Inherit(cocos2d::Node)
{
	CLASS_ESSENTAIL(TaskItem)
public:
	static TaskItem*  create(const TaskInfo& tinfo);

	bool init(const TaskInfo& tinfo);
private:
	//放弃放弃按钮点击回调函数
	void onGiveUpBtnClick(cocos2d::CCObject* sender);

	int m_index;   //任务索引
	std::string m_submitMen;  //提交人
};


#endif // !__TASK_ITEM_H__

