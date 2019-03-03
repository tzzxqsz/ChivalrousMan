#include"FriendLayer.h"
#include"Commen.h"
#include"GameData.h"
#include"SynsTask.h"
#include"DBDao.h"
#include"FriendItem.h"
#include"ShareData.h"
#include"FriendManager.h"

bool FriendLayer::init()
{
	if (CommonTouchLayer::init())
	{
		auto size = SCREEN;
		auto bg = Sprite::create(StringValue("StyleBg"));
		bg->setPosition(size.width*0.5, size.height*0.5);
		this->addChild(bg);
		setExcludeRect(bg->getPosition(), bg->getTextureRect());

		auto tabBtn1 = Button::create(StringValue("CommonBtn"));
		tabBtn1->setTitleText(StringValue("FriendText"));
		tabBtn1->setTitleFontSize(24);
		tabBtn1->setTitleFontName("res/font/font2.ttf");
		tabBtn1->setPosition(Vec2(bg->getPositionX() + bg->getContentSize().width*0.5 + 50, bg->getPositionY() + bg->getContentSize().height*0.5 - 80));
		tabBtn1->addClickEventListener(CC_CALLBACK_1(FriendLayer::onFriendListClick, this));
		this->addChild(tabBtn1);
		auto tabBtn2 = Button::create(StringValue("CommonBtn"));
		tabBtn2->setTitleText(StringValue("AddFriendText"));
		tabBtn2->setTitleFontSize(24);
		tabBtn2->setTitleFontName("res/font/font2.ttf");
		tabBtn2->setPosition(Vec2(tabBtn1->getPositionX(), tabBtn1->getPositionY() - 50));
		tabBtn2->addClickEventListener(CC_CALLBACK_1(FriendLayer::onAddFriendClick, this));
		this->addChild(tabBtn2);

		auto tabBtn3 = Button::create(StringValue("CommonBtn"));
		tabBtn3->setTitleText(StringValue("ApplyListText"));
		tabBtn3->setTitleFontSize(24);
		tabBtn3->setTitleFontName("res/font/font2.ttf");
		tabBtn3->setPosition(Vec2(tabBtn2->getPositionX(), tabBtn2->getPositionY() - 50));
		tabBtn3->addClickEventListener(CC_CALLBACK_1(FriendLayer::onApplyListClick, this));
		this->addChild(tabBtn3);

		m_title = LabelTTF::create(StringValue("FriendText"), "res/font/font2.ttf", 24);
		m_title->setPosition(size.width*0.5, size.height*0.5 + bg->getContentSize().height*0.5 - 44);
		this->addChild(m_title);

		m_listView = ListView::create();
		m_listView->setDirection(ui::ScrollView::Direction::VERTICAL);
		m_listView->setPosition(Vec2(bg->getPositionX() - bg->getContentSize().width*0.5 + 30, bg->getPositionY() - bg->getContentSize().height*0.5 + 20));
		m_listView->setContentSize(Size(bg->getContentSize().width - 40, bg->getContentSize().height - 80));
		m_listView->addEventListenerScrollView(this, scrollvieweventselector(FriendLayer::onEventScrollTrigger));
		this->addChild(m_listView);
		//m_listView->add

		return true;
	}
	return false;
}

void FriendLayer::onFriendListClick(cocos2d::CCObject * sender)
{
	m_title->setString(StringValue("FriendText"));
	onSelected(1);
}

void FriendLayer::onAddFriendClick(cocos2d::CCObject * sender)
{
	m_title->setString(StringValue("AddFriendText"));
	onSelected(2);
}

void  FriendLayer::onApplyListClick(cocos2d::CCObject* sender)
{
	m_title->setString(StringValue("ApplyListText"));
	onSelected(3);
}

void FriendLayer::onEventScrollTrigger(cocos2d::CCObject * sender, cocos2d::ui::ScrollviewEventType type)
{
	switch (type)
	{
	default:
		break;
	}
}

void FriendLayer::onSelected(const int & index)
{
	if (m_selectIndex == index)
		return;
	m_selectIndex == index;
	refreshView();
}

void FriendLayer::onEnter()
{
	CommonTouchLayer::onEnter();
	FriendManager::getInstance()->getFriendList(true);
	m_selectIndex = 1;
}

void FriendLayer::refreshView()
{
	std::vector<Player_Info> list;
	switch (m_selectIndex)
	{
	case 1:
		list = FriendManager::getInstance()->getFriendList();
		break;
	case 2:
		list = FriendManager::getInstance()->getAddFriendList();
		break;
	case 3:
		list = FriendManager::getInstance()->getApplyFriendList();
		break;
	default:
		break;
	}
	m_listView->removeAllChildren();
	for (auto var : list)
	{
		auto item = FriendItem::createFriendItem(var);
		m_listView->pushBackCustomItem(item);
	}
}

