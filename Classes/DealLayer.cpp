#include"DealLayer.h"
#include"GameData.h"
#include"Commen.h"
#include"GameScene.h"
#include"GameLogicLayer.h"
#include"Medication.h"
#include"EquipMent.h"
#include"PlayerData.h"
#include"CameraPlayer.h"
#include"TipLayer.h"
#include"GameDynamicData.h"
#include<fstream>

#define BASENUM 8

/*
*������Ʒ
*/
#define ADD_THING(__NAME__)   \
std::ifstream fin;      \
fin.open(name, std::ios::in);     \
if (fin.fail())     \
{      \
	return;     \
}      \
std::string obname;    \
fin >> obname;    \
int index=0;    \
do   \
{      \
	fin >> obname;    \
	char filename[40] = { 0 };     \
	sprintf_s(filename, "Thing/%s.png", obname);    \
	auto ob = __NAME__::createWithImage(filename);    \
	float x = index%BASENUM;  \
	float y = index / BASENUM;  \
	x = m_basePoint.x + x*(45 + 10) + 10;  \
	y = m_basePoint.y - y*(45 + 10)+ 5;  \
	ob->setPosition(x, y);   \
	ob->setTarget(this, menu_selector(DealLayer::onClickThingCallBack));   \
    menu->addChild(ob);    \
    ++index;       \
} while (!fin.eof());  fin.close();
 
DealLayer* DealLayer::createWithType(const int& type,const std::string& name)
{
	DealLayer* pRet = new DealLayer;
	if (pRet&&pRet->init(type,name))
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

bool  DealLayer::init(const int& type,const std::string& name)
{
	if (Layer::init())
	{
		auto size = SCREEN;
		auto backpack = Sprite::create(StringValue("DealPack"));
		backpack->setPosition(size.width*0.5, size.height*0.5);
		this->addChild(backpack);
		m_basePoint.x = backpack->getPositionX() - backpack->getContentSize().width*0.5 + 45;
		m_basePoint.y = backpack->getPositionY() + backpack->getContentSize().height*0.5 - 118;

		menu = Menu::create();
		menu->setPosition(0, 0);
		this->addChild(menu);
		auto buyBtn = MenuItemImage::create(StringValue("BuyBtn"),
			StringValue("BuyBtn"), this,menu_selector(DealLayer::onBuyBtnCallBack));
		float x = backpack->getPositionX() + backpack->getContentSize().width*0.5 - 60;
		float y = backpack->getPositionY() - backpack->getContentSize().height*0.5 + 50;
		buyBtn->setPosition(x, y);
		menu->addChild(buyBtn);

		initThingByName(type, name);

		m_selector = Sprite::create(StringValue("Selector"));
		m_selector->setContentSize(Size{ 40,40 });
		m_selector->setPosition(m_basePoint);
		this->addChild(m_selector);

		auto closeBtn = MenuItemImage::create(StringValue("CloseBtn"),
			StringValue("CloseBtn"), this, menu_selector(DealLayer::onCloseBtnCallBack));
		float closex = m_basePoint.x + backpack->getContentSize().width - 90;
		float closey = m_basePoint.y + 60;
		closeBtn->setPosition(closex, closey);
		menu->addChild(closeBtn);
		
		return true;
	}
	return false;
}

void DealLayer::onBuyBtnCallBack(cocos2d::CCObject* sender)
{
	ClickAction();
	if (m_curSelect != nullptr) 
	{
		float money = dynamic_cast<Thing*>(m_curSelect)->getbuyglod();
		checkBuy(money);
	}
}

void DealLayer::onCloseBtnCallBack(cocos2d::CCObject* sender)
{
	ClickAction();
	static_cast<GameScene*>(getParent())->getLogicLayer()->resumeSchedulerAndActions();
	getParent()->removeChild(this);
}

void  DealLayer::initThingByName(const int& type, const std::string& name) 
{
	switch (type)
	{
	case MEDICATION:
	{
		ADD_THING(Medication);
	}
		break;
	case EQUIPMENT:
	{
		ADD_THING(EquipMent);
	}
		break;
	default:
		break;
	}
}

void DealLayer::onClickThingCallBack(cocos2d::CCObject* sender)
{
	Vec2 targetPos = dynamic_cast<Thing*>(sender)->getPosition();
	targetPos.y -= 8;
	targetPos.x -= 9;
	auto move = MoveTo::create(0.2, targetPos);
	m_selector->runAction(move);
	dynamic_cast<Thing*>(sender)->showDetail(this);
	m_curSelect = sender;
}

void DealLayer::checkBuy(float money)
{
	float haveglod = GetPlayerData().getglod();
	if (haveglod < money)
	{
		auto tiplayer = TipLayer::createTipLayer(StringValue("LackGlod"));
		CurGameScene()->addChild(tiplayer);
		return;
	}
	else
	{
		auto tiplayer = TipLayer::createTipLayer(StringValue("BuySuccess"));
		CurGameScene()->addChild(tiplayer);
		GetPlayerData().setglod(haveglod - money);
		return;
	}
}