#include"DetailLayer.h"
#include"tool/GameData.h"
#include"tool/Commen.h"

DetailLayer* DetailLayer::createWithThing(const std::vector<std::string>& details,const int& costValue)
{
	DetailLayer* pRet = new DetailLayer;
	if (pRet&&pRet->init(details, costValue))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool DetailLayer::init(const std::vector<std::string>&details, const int& costValue)
{
	if (Layer::init())
	{
		auto size = SCREEN;
		auto back = Sprite::create(StringValue("DetailBg"));
		back->setPosition(back->getContentSize().width*0.5+10, size.height*0.5);
		this->addChild(back);
		int n = details.size();
		Vec2 lastPos;
		auto name = LabelTTF::create(details[0], "¿¬Ìå", 20);
		name->setAnchorPoint(Vec2(0.5, 0.5));
		name->setPosition(back->getPositionX(), back->getPositionY() + back->getContentSize().height*0.5 - 50);
		this->addChild(name);
		for (int i=1;i<n;++i)
		{
			auto detail = LabelTTF::create(details[i], "¿¬Ìå", 20);
			detail->setAnchorPoint(Vec2(0, 0.5));
			detail->setPosition(back->getPositionX() - back->getContentSize().width*0.5 + 24, back->getPositionY() + back->getContentSize().height*0.5 - 65 - detail->getContentSize().height*i);
			this->addChild(detail);
			lastPos = detail->getPosition();
		}

		std::string cost = StringValue("Cost") + NumberToString(costValue);
		auto sellmoney = LabelTTF::create(cost, "¿¬Ìå", 20);
		sellmoney->setColor(ccc3(255, 242, 0));
		sellmoney->setPosition(back->getPositionX(), lastPos.y - 50);
		this->addChild(sellmoney);

		auto menu = Menu::create();
		menu->setPosition(0, 0);
		this->addChild(menu);

		auto closeBtn = MenuItemImage::create(StringValue("CloseBtn"), StringValue("CloseBtn"),
			this, menu_selector(DetailLayer::onCloseClickCallBack));
		float btnx = back->getPositionX();
		float btny = back->getPositionY() - back->getContentSize().height*0.5 + 40;
		closeBtn->setPosition(btnx, btny);
		menu->addChild(closeBtn);
		return true;
	}
	return false;
}

void DetailLayer::onCloseClickCallBack(cocos2d::CCObject* sender)
{
	ClickAction();
	removeFromParent();
}