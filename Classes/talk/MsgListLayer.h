#pragma once
#ifndef __MSG_LIST_LAYER_H__
#define __MSG_LIST_LAYER_H__
#include"tool/PreProcess.h"
#include"common/CommonTouchLayer.h"
#include<list>

class MsgItem;

class MsgListLayer Inherit(CommonTouchLayer)
{
	CLASS_ESSENTAIL(MsgListLayer)
	CREATE_FUNC(MsgListLayer)
public:
	bool init() override;

	/*
	*removeMsgItem(cocos2d::MenuItemImage* item);
	*ɾ����Ϣitem
	*/
	void removeMsgItem(MsgItem* item);
private:
	/*
	*��ʼ����Ҫ��ʾ����Ϣ�б�
	*@param basePos:��׼λ��
	*/
	void initMsgItem(cocos2d::Vec2 basePos);

	/*
	*item����¼�
	*/
	void onItemClickCallback(cocos2d::CCObject* sender);

	std::list<MsgItem*> m_itemlist;
};

#endif