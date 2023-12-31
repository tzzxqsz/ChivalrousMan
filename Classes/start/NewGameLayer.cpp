#include"NewGameLayer.h"
#include"tool/GameData.h"
#include"StartMenu.h"
#include"tool/Commen.h"
#include"GameScene.h"
#include"tool/GameDynamicData.h"
#include"ExcessiveScene.h"
#include"dbconnect/DBDao.h"
#include"dbconnect/Model.h"
#include"player/CameraPlayer.h"
#include"player/PlayerData.h"
#include"net/SocketManager.h"
#include"player/PlayerManager.h"
#include<functional>
#include<sstream>

#define SetInfo(__TYPE__,NUM)    \
ss <<NUM;  \
ss >> tmp;   \
playerinfo.set##__TYPE__(tmp);  \
GetPlayerData().set##__TYPE__(NUM);   \
ss.clear()

bool NewGameLayer::init()
{
	if (Layer::init())
	{
		LISTEN_TOUCH(NewGameLayer);

		Size size = SCREEN;
		auto back = Sprite::create(StringValue("SigOnBg"), Rect{ 0,0,size.width,size.height });
		back->setPosition(size.width*0.5, size.height*0.5);
		this->addChild(back);

		STONE_STATION(0.25, 0.5,NewGameLayer::onStoneCallBack, this);
		
		m_bracket[0] = Sprite::create(StringValue("LeftBracket"));
		m_bracket[0]->setPosition(SCREEN.width*0.25 - 70, SCREEN.height*0.57);
		m_bracket[1] = Sprite::create(StringValue("RightBracket"));
		m_bracket[1]->setPosition(SCREEN.width*0.25 + 70, SCREEN.height*0.57);
		m_bracket[0]->setScale(0.8);
		auto move = MoveBy::create(0.3, ccp(-20, 0));
		auto move1 = MoveBy::create(0.3, ccp(20, 0));
		auto addmove = Sequence::createWithTwoActions(move, move1);
		m_bracket[0]->runAction(RepeatForever::create(addmove));
		m_bracket[1]->setScale(0.8);
		auto move2 = MoveBy::create(0.3, ccp(20, 0));
		auto move3 = MoveBy::create(0.3, ccp(-20, 0));
		auto addmove1 = Sequence::createWithTwoActions(move2, move3);
		m_bracket[1]->runAction(RepeatForever::create(addmove1));
		this->addChild(m_bracket[0]);
		this->addChild(m_bracket[1]);

		char playername[40] = { 0 };
		for (int i = 0; i < 3; ++i)
		{
			sprintf_s(playername, "Player%dRunDown", i + 1);
			auto playerAnimation = AnimationCache::getInstance()->getAnimation(playername);
			auto playerAnimate = Animate::create(playerAnimation);
			sprintf_s(playername, "Player%dWaitDown", i + 1);
			auto player = Sprite::create(StringValue(playername));
			player->setPosition(SCREEN.width*(0.25 + i*0.25), SCREEN.height*0.625);
			player->runAction(RepeatForever::create(playerAnimate));
			this->addChild(player);
		}

		ADD_EDIT(m_username, "PlayerNameTip", ccp(size.width*0.32, size.height*0.35), "PlayerName", "EditBg", false, this, this);

		COMMEN_BTN(this, NewGameLayer::onConfirmCallBack,
			NewGameLayer::onCancelCallBack);
		return true;
	}

	return false;
}

void NewGameLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	bool res;
	Vec2 pos = touch->getLocation();
	ATTACH_OR_DETACH(m_username, pos, res);
}

void NewGameLayer::onConfirmCallBack(cocos2d::CCObject* sender)
{
	std::string name = m_username->getString();
	std::string nums = GetStringData("rolenums");
	if (std::stoi(nums) >= 3)
	{
		MessageBox("角色数已达上限", "提示");
		return;
	}
	if (name != "")
	{
		DBDao<PlayerInfo> dao;
		PlayerInfo playerinfo;
		constructPlayerInfo(playerinfo, name);
		recordPlayerType(playerinfo);
		dao.setModel(playerinfo);
		if (!dao.insertModel())
		{
			MessageBox("创建失败", "提示");
			return;
		}
		addRoleNums();
		SetStringData("rolename", name);
		PlayerManager::getInstance()->c2sInitPlayerData();
		//SocketManager::getInstance()->SendInitPlayerData();
		auto gamescene = GameScene::createWithLevel(LEVEL_ONE);
		CC_SAFE_RETAIN(gamescene);
		std::function<bool(void)> func = [] {return true; };
		ExcessiveScene* excessive = ExcessiveScene::createExcessice(gamescene, func, 2);
		Director::getInstance()->replaceScene(excessive);
	}
	else
	{
		MessageBeep(2);
		MessageBox("角色名不能为空", "提示");
	}
}

void NewGameLayer::recordPlayerType(PlayerInfo& info)
{
	switch (m_playerType)
	{
	case Player_Type::Player1_Type:
	{
		info.setroleType("Player1");
		SetStringData("PlayerType", "Player1");
	}
		break;
	case Player_Type::Player2_Type:
	{
		info.setroleType("Player2");
		SetStringData("PlayerType", "Player2");
	}
		break;
	case Player_Type::Player3_Type:
	{
		info.setroleType("Player3");
		SetStringData("PlayerType", "Player3");
	}
		break;
	default:
		break;
	}
}

void  NewGameLayer::onCancelCallBack(cocos2d::CCObject* sender)
{
	GO_BACK_START_MENU();
}

bool NewGameLayer::onTextFieldAttachWithIME(cocos2d::TextFieldTTF * sender)
{
	sender->setScale(1.1);
	sender->setTextColor(ccc4(13, 203, 17, 255));
	sender->setColorSpaceHolder(ccc4(255, 128, 0, 255));
	return TextFieldDelegate::onTextFieldAttachWithIME(sender);
}

bool NewGameLayer::onTextFieldDetachWithIME(cocos2d::TextFieldTTF * sender)
{
	sender->setScale(1.0);
	sender->setTextColor(ccc4(131, 3, 92, 255));
	sender->setColorSpaceHolder(ccc3(73, 214, 23));
	return TextFieldDelegate::onTextFieldDetachWithIME(sender);
}

void NewGameLayer::onStoneCallBack(cocos2d::CCObject* sender)
{
	switch (dynamic_cast<MenuItemImage*>(sender)->getTag())
	{
	case 101:
		m_playerType = Player_Type::Player1_Type;
		moveBracket(ccp(SCREEN.width*0.25, SCREEN.height * 0.57), 0.5);
		break;
	case 102:
		m_playerType = Player_Type::Player2_Type;
		moveBracket(ccp(SCREEN.width*0.25 * 2, SCREEN.height*0.57), 0.5);
		break;
	case 103:
		m_playerType = Player_Type::Player3_Type;
		moveBracket(ccp(SCREEN.width*0.25 * 3, SCREEN.height*0.57), 0.5);
		break;
	default:
		break;
	}
}

void NewGameLayer::moveBracket(cocos2d::Vec2 dest, float delay)
{
	auto move = MoveTo::create(delay, ccp(dest.x - 70, dest.y));
	m_bracket[0]->runAction(move);

	auto move1 = MoveTo::create(delay, ccp(dest.x + 70, dest.y));
	m_bracket[1]->runAction(move1);
}

void NewGameLayer::addRoleNums()
{
	DBDao<GamePlayer> dao;
	GamePlayer player;
	std::string rolenums = GetStringData("rolenums");
	int num = std::stoi(rolenums) + 1;
	std::stringstream ss;
	ss << num;
	ss >> player[3];
	dao.setModel(player);
	dao.updateModel("playername", GetStringData("playername"));
}

void NewGameLayer::constructPlayerInfo(PlayerInfo& playerinfo,const std::string& name)
{
	std::stringstream ss;
	std::string tmp;
	playerinfo.setplayerName(GetStringData("playername"));
	playerinfo.setroleName(name);
	SetInfo(attack, 100);
	SetInfo(blood, 300);
	SetInfo(defense, 20);
	SetInfo(glod, 300);
	SetInfo(grade, 1);
	SetInfo(mana, 150);
	SetInfo(speed, 4);
	SetInfo(exp, 0);
	SetInfo(maxExp, 100);
	CameraPlayer::getPlayerInstance()->setTeamStatus(P_STATUS_NORMAL);
	playerinfo.setdestx("100");
	playerinfo.setdesty("100");
	playerinfo.setlevel(NTS(LEVEL_ONE));
}