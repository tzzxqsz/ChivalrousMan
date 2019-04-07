#pragma once
#ifndef __SEACT_ACTIVE_LAYER_H__
#define __SEACT_ACTIVE_LAYER_H__
#include"common/CommonTouchLayer.h"
#include"ui/UIImageView.h"
#include"ui/UIButton.h"
#include"ui/UIListView.h"

class CommonProcessBar;
class CommonButton;

class SectActiveLayer :public CommonTouchLayer
{
public:
	CREATE_FUNC(SectActiveLayer)

    bool init() override;

	void updateUI(const std::string& name);

	void onBackClickCallback(cocos2d::CCObject* sender);

	void onXiulianClickCallback(cocos2d::CCObject* sender);

	void onGongfaClickCallback(cocos2d::CCObject* sender);

	void onOneXiulianClickCallback(cocos2d::CCObject* sender);

	void onOnceXiulianClickCallback(cocos2d::CCObject* sender);

	void onClicked() override;
private:

	void updateDec();

	void updateAttrs();

	void initXiulian();

	void initGongfa();

	void updateXiulianView();

	cocos2d::ui::ImageView* m_imageBg;
	cocos2d::Node* m_nodeDec;
	cocos2d::Label* m_title;
	cocos2d::ui::Button* m_xiulian;
	cocos2d::ui::Button* m_gongfa;

	//-- ÐÞÁ¶
	cocos2d::Node* m_nodeXiulian;
	cocos2d::Label* m_gongfaName;
	cocos2d::Label* m_jingjie;
	cocos2d::LabelTTF* m_stoneNums;
	cocos2d::ui::ImageView* m_avatar;
	CommonProcessBar* m_curProcess;
	CommonButton* m_btnOnce;  //ÐÞÁ¶
	CommonButton* m_btnOneKey;  //Ò»¼üÐÞÁ¶
	//

	//
	cocos2d::Node* m_nodeGongfa;
	cocos2d::ui::ListView* m_listview;
	//
	std::string m_name;
};

#endif // !__SEACT_ACTIVE_LAYER_H__

