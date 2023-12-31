#include"GameUILayer.h"
#include"tool/Commen.h"
#include"tool/GameData.h"
#include"tool/GameDynamicData.h"
#include"GameMenuLayer.h"
#include"skill/SkillLayer.h"
#include"backpack/BackPackLayer.h"
#include"WorldMapLayer.h"
#include"GameScene.h"
#include"GameLogicLayer.h"
#include"player/CameraPlayer.h"
#include"RoleInfoLayer.h"
#include"player/CameraPlayer.h"
#include"task/TaskLayer.h"
#include"player/PlayerListLayer.h"
#include"talk/MsgListLayer.h"
#include"team/TeamLayer.h"
#include"friend/FriendLayer.h"
#include"net/SocketManager.h"
#include"talk/TalkManager.h"
#include"talisman/TalismanLayer.h"
#include"sect/SectMainLayer.h"
#include"common/CommonButton.h"
#include"sect/SectActiveLayer.h"
#include"tool/Path.h"
#include<string>

#define SHOW_LAYER(__LAYER__)  \
	auto layer = __LAYER__::create();      \
	layer->setName(#__LAYER__);      \
    layer->setZOrder(this->getZOrder()+1);   \
	getParent()->addChild(layer)     

bool GameUILayer::init()
{
	if (Layer::init())
	{
		setName("GameUILayer");
		generateUserInterface();

		return true;
	}
	return false;
}

void GameUILayer::generateUserInterface()
{
	auto size = SCREEN;
	LISTEN_TOUCH(GameUILayer);

	auto menu = Menu::create();
	menu->setPosition(0, 0);
	this->addChild(menu);

	auto headFrame = Sprite::create(StringValue("HeadFrame"));
	headFrame->setPosition(headFrame->getContentSize().width*0.5 + 10, size.height - headFrame->getContentSize().height*0.5 - 15);
	this->addChild(headFrame);
	char headname[40] = { 0 };
	sprintf_s(headname, "%sHead", GetStringData("PlayerType").c_str());
	m_head = MenuItemImage::create(StringValue(headname),
		StringValue(headname), this,
		menu_selector(GameUILayer::onHeadClickCallBack));
	m_head->setPosition(headFrame->getPosition().x - 5, headFrame->getPosition().y + 5);
	menu->addChild(m_head);

	auto labelgrade = LabelTTF::create(StringValue("GradeText"), "楷体", 20);
	labelgrade->setColor(ccc3(0, 0, 0));
	labelgrade->setPosition(labelgrade->getContentSize().width*0.5 + 20, size.height - headFrame->getContentSize().height - 25);
	this->addChild(labelgrade);
	m_grade = LabelTTF::create(NumberToString(GetPlayerData().getgrade()), "楷体", 20);
	m_grade->setPosition(labelgrade->getPosition().x + labelgrade->getContentSize().width, labelgrade->getPosition().y);
	this->addChild(m_grade);
	
	m_roleName = LabelTTF::create(GetStringData("rolename"), "楷体", 20);
	m_roleName->setPosition(labelgrade->getPosition().x, labelgrade->getPosition().y - 20);
	this->addChild(m_roleName);

	m_backpack = MenuItemImage::create(StringValue("BackPack"), 
		StringValue("BackPack"),this,
		menu_selector(GameUILayer::onBackPackClickCallBack));
	m_backpack->setPosition(size.width - m_backpack->getContentSize().width*0.5 - 15, m_backpack->getContentSize().height*0.5 + 10);
	m_skill = MenuItemImage::create(StringValue("SkillIcon"),
		StringValue("SkillIcon"), this,
		menu_selector(GameUILayer::onSkillClickCallBack));
	m_skill->setPosition(m_backpack->getPosition().x - m_backpack->getContentSize().width - 20, m_backpack->getPosition().y - 5);
	menu->addChild(m_backpack);
	menu->addChild(m_skill);
	m_taskItem = MenuItemImage::create(StringValue("TaskIcon"), StringValue("TaskIcon"),
		this, menu_selector(GameUILayer::onTaskIconClickCallback));
	m_taskItem->setPosition(m_skill->getPositionX() - m_skill->getContentSize().width - 15, m_skill->getPositionY());
	menu->addChild(m_taskItem);
	auto npplayer = MenuItemImage::create(StringValue("NearPlayer"), StringValue("NearPlayer"), this,
		menu_selector(GameUILayer::onNearPlayerBtnClick));
	npplayer->setPosition(m_taskItem->getPositionX() - m_taskItem->getContentSize().width - 15, m_taskItem->getPositionY());
	menu->addChild(npplayer);
	m_msgicon = MenuItemImage::create(StringValue("MsgIcon"), StringValue("MsgIcon"),
		this, menu_selector(GameUILayer::onMsgIconClickCallback));
	m_msgicon->setPosition(npplayer->getPositionX() - npplayer->getContentSize().width - 15, npplayer->getPositionY() - 4);
	menu->addChild(m_msgicon);
	auto teamIcon = MenuItemImage::create(StringValue("TeamIcon"), StringValue("TeamIcon"), this,
		menu_selector(GameUILayer::onTeamIconClick));
	teamIcon->setPosition(m_msgicon->getPositionX() - m_msgicon->getContentSize().width - 15, m_msgicon->getPositionY()+3);
	menu->addChild(teamIcon);
	auto friendBtn = MenuItemImage::create(StringValue("FriendBtn"), StringValue("FriendBtn"), this, menu_selector(GameUILayer::onFriendClickCallback));
	friendBtn->setPosition(teamIcon->getPositionX() - teamIcon->getContentSize().width - 15, teamIcon->getPositionY());
	menu->addChild(friendBtn);
	
	auto talismanBtn = CommonButton::createCommonButton(getButtonPath("btn_talisman"));
	this->addChild(talismanBtn);
	talismanBtn->setPosition(friendBtn->getPositionX() - friendBtn->getContentSize().width - 15, friendBtn->getPositionY()+10);
	talismanBtn->addClickCallback(CC_CALLBACK_1(GameUILayer::onTalismanClickCallback, this));

	auto sectBtn = CommonButton::createCommonButton(getButtonPath("Sect_btn"));
	this->addChild(sectBtn);
	sectBtn->setPosition(talismanBtn->getPositionX() - talismanBtn->getContentSize().width - 10, talismanBtn->getPositionY()-10);
	sectBtn->addClickCallback(CC_CALLBACK_1(GameUILayer::onSectClickCallback, this));

	m_teamSpot = Sprite::create(StringValue("MsgTip"));
	m_teamSpot->setPosition(teamIcon->getPositionX() + 20, teamIcon->getPositionY() + 10);
	this->addChild(m_teamSpot);
	m_teamSpot->setVisible(false);
	m_redSpot = Sprite::create(StringValue("MsgTip"));
	m_redSpot->setPosition(m_msgicon->getPositionX() + 20, m_msgicon->getPositionY() + 10);
	this->addChild(m_redSpot);
	m_redSpot->setVisible(false);
	m_worldMap = MenuItemImage::create(StringValue("MapIcon"),
		StringValue("MapIcon"), this,
		menu_selector(GameUILayer::onMapIconClickCallBack));
	m_worldMap->setPosition(size.width - m_worldMap->getContentSize().width*0.5, size.height - m_worldMap->getContentSize().height*0.5 - 20);
	menu->addChild(m_worldMap);

	m_menuBtn = MenuItemImage::create(StringValue("MenuBtn"),
		StringValue("MenuBtn"), this,
		menu_selector(GameUILayer::onMenuClickCallBack));
	m_menuBtn->setPosition(m_worldMap->getPosition().x - m_worldMap->getContentSize().width, m_worldMap->getPosition().y);
	menu->addChild(m_menuBtn);

	auto bloodBg = Sprite::create(StringValue("BarBg"));
	bloodBg->setPosition(headFrame->getPosition().x + headFrame->getContentSize().width + 15, headFrame->getPosition().y + 20);
	auto manaBg = Sprite::create(StringValue("BarBg"));
	manaBg->setPosition(headFrame->getPosition().x + headFrame->getContentSize().width + 15, headFrame->getPosition().y - 8);
	auto expBg = Sprite::create(StringValue("BarBg"));
	expBg->setPosition(headFrame->getPosition().x + headFrame->getContentSize().width + 15, headFrame->getPosition().y - 35);
	auto bloodBar = Sprite::create(StringValue("BloodBar"));
	m_bloodBar = ProgressTimer::create(bloodBar);
	m_bloodBar->setType(ProgressTimer::Type::BAR);
	m_bloodBar->setMidpoint(ccp(0, 0));
	m_bloodBar->setBarChangeRate(ccp(1, 0));
	m_bloodBar->setPercentage(100);
	m_bloodBar->setPosition(bloodBg->getPosition());
	auto manaBar = Sprite::create(StringValue("ManaBar"));
	m_manaBar = ProgressTimer::create(manaBar);
	m_manaBar->setType(ProgressTimer::Type::BAR);
	m_manaBar->setMidpoint(ccp(0, 0));
	m_manaBar->setBarChangeRate(ccp(1, 0));
	m_manaBar->setPercentage(100);
	m_manaBar->setPosition(manaBg->getPosition());
	auto expBar = Sprite::create(StringValue("ExpBar"));
	m_expBar = ProgressTimer::create(expBar);
	m_expBar->setType(ProgressTimer::Type::BAR);
	m_expBar->setMidpoint(ccp(0, 0));
	m_expBar->setBarChangeRate(ccp(1, 0));
	m_expBar->setPercentage((GetPlayerData().getexp() / GetPlayerData().getmaxExp()) * 100);
	m_expBar->setPosition(expBg->getPosition());

	m_talkFrame = Sprite::create(StringValue("TalkFrame"));
	m_talkFrame->setPosition(m_talkFrame->getContentSize().width*0.5, m_talkFrame->getContentSize().height*0.5 + 30);
	auto label = LabelTTF::create(StringValue("TalkTip"), "楷体", 20);
	label->setPosition(ccp(label->getContentSize().width*0.5, m_talkFrame->getPosition().y + m_talkFrame->getContentSize().height*0.5 + 15));

	auto editBg = Sprite::create(StringValue("MessageFrame"));
	editBg->setPosition(editBg->getContentSize().width*0.5, editBg->getContentSize().height*0.5);
	m_editFrame = TextFieldTTF::textFieldWithPlaceHolder(StringValue("TalkEditECHO"), "楷体", 16);
	m_editFrame->setColor(ccc3(195, 195, 195));
	m_editFrame->setContentSize(editBg->getContentSize());
	m_editFrame->setPosition(editBg->getPosition());
	m_editFrame->setWidth(130);
	m_editFrame->setDelegate(this);
	m_sendBtn = MenuItemImage::create(StringValue("SendBtn"), StringValue("SendBtn"),
		this, menu_selector(GameUILayer::onSendClickCallBack));
	m_sendBtn->setPosition(editBg->getPosition().x + editBg->getContentSize().width*0.5 + 20, editBg->getPosition().y);
	menu->addChild(m_sendBtn);
	this->addChild(editBg);
	this->addChild(m_editFrame);

	std::string glodtext = StringValue("Glod") + ":" + NumberToString(GetPlayerData().getglod());
	m_glodlabel = LabelTTF::create(glodtext, "楷体", 20);
	m_glodlabel->setColor(Color3B::YELLOW);
	m_glodlabel->setPosition(size.width*0.5, size.height - 40);
	this->addChild(m_glodlabel);

	this->addChild(bloodBg);
	this->addChild(manaBg);
	this->addChild(expBg);
	this->addChild(m_bloodBar);
	this->addChild(m_manaBar);
	this->addChild(m_expBar);
	this->addChild(m_talkFrame);
	this->addChild(label);
	scheduleUpdate();
}

void GameUILayer::onMapIconClickCallBack(cocos2d::CCObject* sender)
{
	ClickAction();
	SHOW_LAYER(WorldMapLayer);
}

void GameUILayer::onBackPackClickCallBack(cocos2d::CCObject* sender)
{
	ClickAction();
	SHOW_LAYER(BackPackLayer);
}

void GameUILayer::onSkillClickCallBack(cocos2d::CCObject* sender)
{
	ClickAction();
	SHOW_LAYER(SkillLayer);
}

void GameUILayer::onHeadClickCallBack(cocos2d::CCObject* sender)
{
	ClickAction();
	SHOW_LAYER(RoleInfoLayer);
}

void GameUILayer::onSendClickCallBack(cocos2d::CCObject* sender)
{
	ClickAction();
	if (m_editFrame->getString() != "")
	{
		TalkManager::getInstance()->c2sWorkTalk(m_editFrame->getString());
		m_editFrame->setString("");
	}
}

void GameUILayer::onMenuClickCallBack(cocos2d::CCObject* sender)
{
	ClickAction();
	if (!m_isclickGameMenuLayer)
	{
		m_isclickGameMenuLayer = !m_isclickGameMenuLayer;
		((GameScene*)this->getParent())->pauseAllActions(getParent(), this);
		auto menuLayer = GameMenuLayer::create();
		this->addChild(menuLayer);
	}
}

void GameUILayer::onTaskIconClickCallback(cocos2d::CCObject* sender)
{
	ClickAction(sender);
	SHOW_LAYER(TaskLayer);
}

void GameUILayer::onNearPlayerBtnClick(cocos2d::CCObject* sender)
{
	ClickAction(sender);
	SHOW_LAYER(PlayerListLayer);
}

bool GameUILayer::onTextFieldAttachWithIME(TextFieldTTF * sender)
{
	sender->setScale(1.1);
	sender->setColor(ccc3(255, 255, 255));
	CurGameScene()->pauseAllActions(CurGameScene(), this);
	return TextFieldDelegate::onTextFieldAttachWithIME(sender);
}

bool  GameUILayer::onTextFieldDetachWithIME(TextFieldTTF * sender)
{
	sender->setScale(1.0);
	sender->setColor(ccc3(195, 195, 195));
	CurGameScene()->resumeAllActions(CurGameScene());
	return TextFieldDelegate::onTextFieldDetachWithIME(sender);
}
void GameUILayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	auto pos = touch->getLocation();
	bool res;
	ATTACH_OR_DETACH(m_editFrame, pos, res);
}

void GameUILayer::resetMenulayer()
{
	m_isclickGameMenuLayer = false;
}

void GameUILayer::update(float dt)
{
	std::string glodtext = StringValue("Glod") + ":" + NumberToString(GetPlayerData().getglod());
	m_glodlabel->setString(glodtext);
	m_expBar->setPercentage((GetPlayerData().getexp() / GetPlayerData().getmaxExp()) * 100);
}

void GameUILayer::updateWorldTalkQueue(const TalkMsg& msg)
{
	auto talklabel = LabelTTF::create(msg.rolename + StringValue("Say") + ":" + msg.msg, "楷体", 15);
	cocos2d::Vec2 pos = m_talkFrame->getPosition();
	pos.x = pos.x - m_talkFrame->getContentSize().width*0.5 + 8;
	pos.y = pos.y - m_talkFrame->getContentSize().height*0.5 + 22;
	talklabel->setColor(Color3B::BLACK);
	talklabel->setAnchorPoint(ccp(0, 0.5));
	talklabel->setPosition(pos);
	this->addChild(talklabel);
	for (auto var : m_worldTalkQueue)
	{
		var->setPositionY(var->getPositionY() + 18);
	}
	m_worldTalkQueue.push_back(talklabel);
	if (m_worldTalkQueue.size()>5)
	{
		this->removeChild(m_worldTalkQueue.front());
		m_worldTalkQueue.pop_front();
	}
}

void GameUILayer::onMsgIconClickCallback(cocos2d::CCObject* sender)
{
	ClickAction(sender);
	setRedSpot(false);
	SHOW_LAYER(MsgListLayer);
}

void GameUILayer::onTeamIconClick(cocos2d::CCObject* sender)
{
	ClickAction(sender);
	setTeamSpot(false);
	SHOW_LAYER(TeamLayer);
}

void GameUILayer::onFriendClickCallback(cocos2d::CCObject* sender)
{
	ClickAction(sender);
	SHOW_LAYER(FriendLayer);
}

void GameUILayer::onTalismanClickCallback(cocos2d::CCObject * sender)
{
	SHOW_LAYER(TalismanLayer);
}

void GameUILayer::onSectClickCallback(cocos2d::CCObject * sender)
{
	if (GetPlayerData().getSect() == "")
	{
		SHOW_LAYER(SectMainLayer);
	}
	else
	{
		SHOW_LAYER(SectActiveLayer);
		layer->updateUI(GetPlayerData().getSect());
	}
}

void GameUILayer::setRedSpot(bool b)
{
	m_redSpot->setVisible(b);
}

void GameUILayer::setTeamSpot(bool b)
{
	m_teamSpot->setVisible(b);
}