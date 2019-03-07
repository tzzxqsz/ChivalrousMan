#pragma once
#ifndef __FRIEND_LAYER_H__
#define __FRIEND_LAYER_H__
#include"PreProcess.h"
#include"CommonTouchLayer.h"
#include"ui/UIButton.h"
#include"ui/UIListView.h"
#include"Event.h"
#include"Model.h"
#include<vector>

class FriendLayer :public CommonTouchLayer
{
	CLASS_ESSENTAIL(FriendLayer)
public:
	CREATE_FUNC(FriendLayer)

		virtual bool init() override;

	void onFriendListClick(cocos2d::CCObject* sender);

	void onAddFriendClick(cocos2d::CCObject* sender);

	void onApplyListClick(cocos2d::CCObject* sender);

	void onEventScrollTrigger(cocos2d::CCObject* sender, cocos2d::ui::ScrollviewEventType type);

	void onSelected(const int& index);

	virtual void onEnter() override;

	virtual void onExit() override;

	void refreshView();
private:
	int m_selectIndex = 0;
	cocos2d::ui::ListView* m_listView;
	std::vector<Friend> m_friendList;
	cocos2d::LabelTTF* m_title;

	Slot* m_slot;
};

#endif // !__FRIEND_LAYER_H__

