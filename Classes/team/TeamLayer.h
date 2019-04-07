#pragma once
#ifndef __TEAM_LAYER_H__
#define  __TEAM_LAYER_H__
#include"tool/PreProcess.h"
#include"common/CommonTouchLayer.h"
#include<list>

class TeamLayer Inherit(CommonTouchLayer)
{
	CLASS_ESSENTAIL(TeamLayer)
	CREATE_FUNC(TeamLayer)
public:
	bool init();

	/*
	*ɾ����Ϣitem
	*/
	void removeMsgItem(cocos2d::Node* item);
private:
	/*
	*��ʼ�������б�
	*/
	void initApplyList(const cocos2d::Vec2& basePos);

	/*
	*��ʼ�������Ա
	*/
	void initTeamMember(const cocos2d::Vec2& basePos);

	std::list<cocos2d::Node*> m_itemlist;
};

#endif //!__TEAM_LAYER_H__
