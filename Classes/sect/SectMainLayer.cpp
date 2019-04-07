#include "SectMainLayer.h"
#include"tool/Commen.h"
#include"tool/Path.h"
#include"ui/UIButton.h"
#include"tool/Colors.h"
#include"tool/GameData.h"
#include"SectRukou.h"
#include"event/SignalConst.h"
#include"event/SignalManager.h"
#include"player/CameraPlayer.h"
#include"SectManager.h"
#include"SectActiveLayer.h"

bool SectMainLayer::init()
{
	if (CommonTouchLayer::init())
	{
		auto size = SCREEN;
		auto bg = Sprite::create(getBackgroundPath("StyleBg7"));
		this->addChild(bg);
		bg->setPosition(size.width*0.5, size.height*0.5);
		setExcludeRect(bg->getPosition(), Rect(0, 0, size.width + 400, size.height + 400));

		auto backBtn = ui::Button::create(getButtonPath("back_btn"));
		this->addChild(backBtn);
		backBtn->setPosition(Vec2(backBtn->getContentSize().width*0.5 + 5, size.height - 34));
		backBtn->addClickEventListener(CC_CALLBACK_1(SectMainLayer::onBackClickCallback, this));

		TTFConfig ttfConfig;
		ttfConfig.fontFilePath = getFontPath("font2"); //±ØÐëÅäÖÃ
		ttfConfig.fontSize = 45;
		auto text = Label::createWithTTF(ttfConfig, StringValue("SectText"));
		text->setColor(FRAGMENT_COLOR);
		this->addChild(text);
		text->setPosition(size.width*0.5, size.height - 30);

		ttfConfig.fontSize = 26;
		auto textdesc = Label::createWithTTF(ttfConfig, StringValue("SectDesc"));
		this->addChild(textdesc);
		textdesc->setPosition(size.width*0.5, size.height - 70);

		auto list = std::vector<std::string>{ "leishen","haishen","mingwang" };
		for (int i = 0; i < SectManager::SECT_NUMS; ++i)
		{
			auto rukou = SectRukou::create();
			rukou->updateUI(list[i]);
			rukou->setPosition((rukou->getRokouSize().width)*i + 160, size.height*0.5);
			rukou->addJoinClickCallback(CC_CALLBACK_1(SectMainLayer::onClickJoinSectCallback, this));
			this->addChild(rukou);
		}
		return true;
	}
	return false;
}

void SectMainLayer::onBackClickCallback(cocos2d::CCObject * sender)
{
	this->removeFromParent();
}

void SectMainLayer::onClickJoinSectCallback(cocos2d::CCObject * sender)
{
	auto name = dynamic_cast<Node*>(sender)->getName();
	if (GetPlayerData().getgrade() >= SectManager::LIMIT_LEVEL)
	{
		bool bret=SectManager::getInstance()->joinSect(name);
		if (bret)
		{
			Json::Value msg;
			msg["content"] = StringValue("JoinSectSuccess");
			SignalManager::getInstance()->dispatch(EVENT_TIPS, msg);
			GetPlayerData().setSect(name);
			gotoSectActiveLayer();
		}
	}
	else
	{
		Json::Value msg;
		msg["content"] = StringValue("GradeLack");
		SignalManager::getInstance()->dispatch(EVENT_TIPS, msg);
	}
}

void SectMainLayer::gotoSectActiveLayer()
{
	auto layer = SectActiveLayer::create();
	layer->updateUI(GetPlayerData().getSect());
	layer->setZOrder(this->getZOrder());
	getParent()->addChild(layer);
	removeFromParent();
}
