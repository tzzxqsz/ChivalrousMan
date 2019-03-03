#pragma once
#ifndef __FRIEND_ITEM_H__
#define __FRIEND_ITEM_H__
#include"PreProcess.h"
#include"ui/UILayout.h"
#include"ui/UIButton.h"
#include<initializer_list>
#include<vector>

struct Player_Info;

class FriendItem :public cocos2d::ui::Layout
{
	CLASS_ESSENTAIL(FriendItem)
public:
	CreateWithParam(FriendItem, Player_Info);

	bool init(const Player_Info& info);

	void setStatus(const std::initializer_list<bool>& list);

	void onBtnClick(cocos2d::CCObject* sender);
private:
	std::vector<cocos2d::ui::Button*> m_btnVec;
};

#endif // !__FRIEND_ITEM_H__