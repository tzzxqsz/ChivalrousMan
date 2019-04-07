#pragma once
#ifndef __TALISMAN_AVATAR_H__
#define __TALISMAN_AVATAR_H__
#include"base/Thing.h"
#include"ui/UIImageView.h"

class TalismanAvatar :public cocos2d::Node
{
public:
	static TalismanAvatar* create();

	virtual bool init() override;

	virtual void onEnter() override;

	void updateAvatar(const std::string& name);
private:
	TalismanAvatar();
	~TalismanAvatar();

	cocos2d::ui::ImageView* m_avatar;
};

#endif // !__TALISMAN_AVATAR_H__
