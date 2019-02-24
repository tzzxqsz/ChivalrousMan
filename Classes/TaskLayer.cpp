#include"TaskLayer.h"
#include"Commen.h"
#include"GameData.h"
#include"TaskItem.h"

bool TaskLayer::init()
{
	if (CommonTouchLayer::init())
	{
		auto size = SCREEN;
		auto bg = Sprite::create(StringValue("TaskBg"));
		bg->setPosition(size.width*0.5, size.height*0.5);
		this->addChild(bg);
		setExcludeRect(bg->getPosition(), bg->getTextureRect());
		auto labeltitle = LabelTTF::create(StringValue("TaskTitle"), "¿¬Ìå", 30);
		labeltitle->setPosition(size.width*0.5, size.height*0.5 + bg->getContentSize().height*0.5 - 25);
		labeltitle->setColor(Color3B::YELLOW);
		this->addChild(labeltitle);
		
		initTaskItem(bg->getPosition());
		return true;
	}
	return false;
}

void TaskLayer::initTaskItem(cocos2d::Vec2 basePos)
{
	basePos.y += 202;
	int index = 0;
	for (auto var : TaskSystem::getInstance()->getpickedupTask())
	{
		TaskItem* taskitem = TaskItem::create(var);
		taskitem->setPosition(basePos.x, basePos.y - index * 80);
		this->addChild(taskitem);
		m_itemlist.push_back(taskitem);
		++index;
		if (index > 6)
		{
			return;
		}
	}
}

void TaskLayer::removeTaskItem(TaskItem* item)
{
	for (auto it = m_itemlist.begin(); it != m_itemlist.end();)
	{
		if (*it == item)
		{
			it = m_itemlist.erase(it);
			this->removeChild(item);
		}
		else
		{
			auto move = MoveBy::create(0.2, ccp(0, 80));
			(*it)->runAction(move);
			++it;
		}
	}
}