#include"BackPackLayer.h"
#include"tool/GameData.h"
#include"player/CameraPlayer.h"
#include"tool/Commen.h"
#include"backpack/BackPackManager.h"
#include"base/Thing.h"
#include"base/Medication.h"
#include"equipment/EquipMent.h"
#include"common/TipLayer.h"
#include"talisman/TalismanFragment.h"
#include<string>
#include<map>

#define BASENUM 8

bool BackPackLayer::init()
{
	if (CommonTouchLayer::init())
	{
		auto size = SCREEN;
		auto backpackGrid = Sprite::create(StringValue("BackpackGrid"));
		backpackGrid->setPosition(size.width*0.5, size.height*0.5);
		this->addChild(backpackGrid);
		setExcludeRect(backpackGrid->getPosition(), backpackGrid->getTextureRect());
		m_basePoint.x = backpackGrid->getPositionX() - backpackGrid->getContentSize().width*0.5 + 45;
		m_basePoint.y = backpackGrid->getPositionY() + backpackGrid->getContentSize().height*0.5 - 118;
		
		m_menu = Menu::create();
		m_menu->setPosition(0, 0);
		this->addChild(m_menu);
		
		auto sellBtn = MenuItemImage::create(StringValue("SellBtn"), StringValue("SellBtn"),
			this, menu_selector(BackPackLayer::sellBtnCallback));
		float sellX = backpackGrid->getPositionX() + backpackGrid->getContentSize().width*0.5 - sellBtn->getContentSize().width;
		float sellY = backpackGrid->getPositionY() - backpackGrid->getContentSize().height*0.5 + sellBtn->getContentSize().height;
		sellBtn->setPosition(sellX, sellY);
		m_menu->addChild(sellBtn);

		auto useBtn = MenuItemImage::create(StringValue("UseBtn"),
			StringValue("UseBtn"), this,
			menu_selector(BackPackLayer::useBtnCallBack));
		float usex = sellBtn->getPositionX() - sellBtn->getContentSize().width - 20;
		float usey = sellBtn->getPositionY();
		useBtn->setPosition(usex, usey);
		m_menu->addChild(useBtn);

		auto bp1Btn = MenuItemImage::create(StringValue("Bp1Btn"),
			StringValue("Bp1SBtn"),this,
			menu_selector(BackPackLayer::bp1BtnCallBack));
		float bp1x = m_basePoint.x + 20;
		float bp1y = m_basePoint.y + 60;
		bp1Btn->setPosition(bp1x, bp1y);
		m_menu->addChild(bp1Btn);
		auto bp2Btn = MenuItemImage::create(StringValue("Bp2Btn"),
			StringValue("Bp2SBtn"),this,
			menu_selector(BackPackLayer::bp2BtnCallBack));
		bp2Btn->setPosition(bp1x + bp2Btn->getContentSize().width+10, bp1y);
		m_menu->addChild(bp2Btn);

		m_selector = Sprite::create(StringValue("Selector"));
		m_selector->setContentSize(Size{ 40,40 });
		m_selector->setPosition(m_basePoint);
		this->addChild(m_selector);

		initBackPackThing();

		return true;
	}
	return false;
}

void BackPackLayer::sellBtnCallback(cocos2d::CCObject* sender)
{
	ClickAction();
	if (m_curSel == nullptr)
		return;
	Thing* pth = dynamic_cast<Thing*>(m_curSel);
	int index = pth->getTag();
	int nums = std::stoi(m_numlabels[index]->getString());
	if (nums > 0)
	{
		m_numlabels[index]->setString(NumberToString(nums - 1));
		BackPackManager::getInstance()->removeBackPackThing(pth->getname());
		GetPlayerData().addGlod(pth->getsellglod());
	}
	else
	{
		TipLayer* tiplayer = TipLayer::createTipLayer(StringValue("LackNums"));
		this->addChild(tiplayer);
	}
}

void BackPackLayer::useBtnCallBack(cocos2d::CCObject* sender)
{
	ClickAction();
	if (m_curSel == nullptr)
		return;
	Thing* pth = dynamic_cast<Thing*>(m_curSel);
	int index = pth->getTag();
	int nums = std::stoi(m_numlabels[index]->getString());
	if (nums > 0)
	{
		if (pth->beUse(this) != -1.0f)
		{
			m_numlabels[index]->setString(NumberToString(nums - 1));
			BackPackManager::getInstance()->removeBackPackThing(pth->getname());
		}
	}
	else
	{
		TipLayer* tiplayer = TipLayer::createTipLayer(StringValue("LackNums"));
		this->addChild(tiplayer);
	}
}

void BackPackLayer::bp1BtnCallBack(cocos2d::CCObject* sender)
{

}

void BackPackLayer::bp2BtnCallBack(cocos2d::CCObject* sender)
{

}

void BackPackLayer::initBackPackThing()
{
	int index = 0;
	for (const auto& it : BackPackMap())
	{
		std::string filename = it.name;
		filename += ".png";
		Thing* ob = nullptr;
		int offsetx = 0;
		int offsety = 0;
		if (it.type == MEDICATION)
		{
			ob = Medication::createWithImage(filename);
		}
		else if (it.type == MW_FRAGMENT)
		{
			ob = TalismanFragment::createWithName();
			dynamic_cast<TalismanFragment*>(ob)->updateUI(it.name, true);
			offsetx = -5;
			offsety = -1;
		}
		else
		{
			ob = EquipMent::createWithImage(filename);
			dynamic_cast<EquipMent*>(ob)->setgrade(it.grade);
		}
		float x = index % BASENUM;
		float y = index / BASENUM;     
		x = m_basePoint.x + x * (55.8) + 9;
		y = m_basePoint.y - y * (55.8) + 7;
		ob->setPosition(x, y);
		ob->addClickCallback(CC_CALLBACK_1(BackPackLayer::onClickThingCallBack, this));
		auto numlabel = LabelTTF::create(NumberToString(it.nums), "����",20);
		numlabel->setPosition(-18, -14);
		numlabel->setColor(ccc3(255, 242, 0));
		ob->addChild(numlabel);
		ob->setTag(index);      //ʹ��tag�洢����
		m_numlabels.push_back(numlabel);
		this->addChild(ob);
		if (!index)
			m_curSel = ob;
		++index;
	}
}

void BackPackLayer::onClickThingCallBack(cocos2d::CCObject* sender)
{
	Vec2 targetPos = dynamic_cast<Thing*>(sender)->getPosition();
	targetPos.y -= 6;
	targetPos.x -= 8;
	auto move = MoveTo::create(0.2, targetPos);
	m_selector->runAction(move);
	dynamic_cast<Thing*>(sender)->showDetail(this);
	m_curSel = sender;
}