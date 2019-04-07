#include"SocketManager.h"
#include"tool/GameData.h"
#include"tool/Commen.h"
#include"jsonCpp/reader.h"
#include"jsonCpp/value.h"
#include"NetWorkManager.h"
#include<fstream>
#include<string>

using namespace Net;

DEFINE_SINGLE_ATTRIBUTES(SocketManager);

SocketManager::SocketManager()
{
	readConfConnectServer();
}

SocketManager::~SocketManager()
{

}

void SocketManager::release()
{
	RELEASE_NULL(m_instance);
}


void  SocketManager::OnRecv(char* buff)
{
	if (!strcmp(buff, CLOSE_MESSAGE))
	{
		MessageBox("服务器异常关闭", "提示");
		Director::getInstance()->end();
	}
	Json::CharReaderBuilder readerBuilder;
	Json::CharReader* reader = readerBuilder.newCharReader();
	Json::Value value;
	std::string error;
	if (reader->parse(buff, buff + strlen(buff), &value, &error))
	{
		NetWorkManager::getInstance()->dispatch(value["MessageId"].asInt(), value);
	}
}

void SocketManager::readConfConnectServer()
{
	std::ifstream fin;
	fin.open(StringValue("ServerConf"), std::ios::in);
	if (fin.fail())
	{
		return;
	}
	std::string tmp;
	
	fin >> m_serverip;

	fin >> m_serverip;
	fin >> m_serverip;
	fin >> tmp;
	fin >> m_port;

	fin.close();
}

int SocketManager::Connect()
{
	return CTCPClient::ConnectSever(m_serverip, m_port);
}

//void SocketManager::SendInitPlayerData()
//{
//	m_playerlist.clear();
//	InitData_Msg msg;
//	msg.type = M_InitData;
//	strcpy_s(msg.playername, GetStringData("playername").c_str());
//	strcpy_s(msg.rolename, GetStringData("rolename").c_str());
//	strcpy_s(msg.playertype, GetStringData("PlayerType").c_str());
//	msg.curmap = GetIntData("CurMap");
//	msg.attack = GetPlayerData().getattack();
//	msg.blood = GetPlayerData().getblood();
//	msg.defense = GetPlayerData().getdefense();
//	msg.mana = GetPlayerData().getmana();
//	msg.grade = GetPlayerData().getgrade();
//	msg.fd = -1;
//	SendMsg((char*)&msg, sizeof(msg));
//}

//void SocketManager::SendInitPos()
//{
//	InitPos_Msg msg;
//	msg.type = M_InitPos;
//	msg.x = PlayerPos.x;
//	msg.y = PlayerPos.y;
//	msg.fd = -1;
//	msg.curmap = GetIntData("CurMap");
//	SendMsg((char*)&msg, sizeof(msg));
//}

//void SocketManager::doInitMsg(InitData_Msg* msg)
//{
//	Player_Info pinfo;
//	pinfo.playername = msg->playername;
//	pinfo.attack = msg->attack;
//	pinfo.blood = msg->blood;
//	pinfo.curmap =msg->curmap;
//	pinfo.defense = msg->defense;
//	pinfo.mana = msg->mana;
//	pinfo.playertype = msg->playertype;
//	pinfo.rolename = msg->rolename;
//	pinfo.fd = msg->fd;
//	pinfo.grade = msg->grade;
//	m_playerlist.push_back(pinfo);
//}

//void SocketManager::doInitPlayerPosMsg(InitPos_Msg* msg)
//{
//	for (auto var=m_playerlist.begin();var!=m_playerlist.end();++var)
//	{
//		if (msg->fd == var->fd)
//		{
//			var->x = msg->x;
//			var->y = msg->y;
//			var->curmap = msg->curmap;
//			if (Director::getInstance()->getRunningScene()->getChildByName("ObjectLayer") != nullptr)
//				CurGameScene()->getObjectLayer()->addPlayer(*var);
//		}
//	}
//}

//void SocketManager::SendPlayerLeaveMsg()
//{
//	PlayerLeave_Msg msg;
//	msg.type = M_PlayerLeave;
//	msg.fd = -1;
//	SendMsg((char*)&msg, sizeof(msg));
//}

//void SocketManager::doPlayerLeaveMsg(PlayerLeave_Msg* msg)
//{
//	removePlayer(msg->fd);
//	auto ftLayer = Director::getInstance()->getRunningScene()->getChildByName("FightLayer");
//	if (ftLayer != nullptr)
//		dynamic_cast<FightLayer*>(ftLayer)->OtherPlayerLeave();
//}

//void SocketManager::removePlayer(int fd)
//{
//	for (auto it = m_playerlist.begin(); it != m_playerlist.end(); ++it)
//	{
//		if (it->fd == fd)
//		{
//			if (Director::getInstance()->getRunningScene()->getChildByName("ObjectLayer") != nullptr)
//				CurGameScene()->getObjectLayer()->removePlayer(it->playername, it->rolename);
//			TeamManager::getInstance()->removeTeamMembers(it->fd);
//	/*		m_privateTalkMsgs.erase(it->fd);*/
//			m_playerlist.erase(it);
//			return;
//		}
//	}
//}

//void SocketManager::SendMoveToMsg(const cocos2d::Vec2& pos,int less)
//{
//	MoveTo_Msg msg;
//	msg.type = M_MoveTo;
//	msg.fd = -1;
//	msg.x = pos.x;
//	msg.y = pos.y;
//	msg.less = less;
//	SendMsg((char*)&msg, sizeof(msg));
//}

//void SocketManager::doPlayerMoveToMsg(MoveTo_Msg* msg)
//{
//	Vec2 target{ msg->x,msg->y };
//	for (auto var : m_playerlist)
//	{
//		if (var.fd == msg->fd)
//		{
//			if (GetIntData("IsHaveGameScene") == 1)
//				CurGameScene()->getObjectLayer()->moveOtherPlayer(var.playername, var.rolename, target, msg->less);
//		}
//	}
//}

//void SocketManager::doPlayerPosVerifyMsg(VerifyPos_Msg* msg)
//{
//	for (auto var=m_playerlist.begin();var!=m_playerlist.begin();++var)
//	{
//		if (var->fd == msg->fd)
//		{
//			var->x = msg->x;
//			var->y = msg->y;
//			if (Director::getInstance()->getRunningScene()->getChildByName("ObjectLayer") != nullptr)
//				CurGameScene()->getObjectLayer()->verifyPlayerPos(var->playername, var->rolename, Vec2{ msg->x,msg->y });
//		}
//	}
//}

//void SocketManager::VerifyPlayerPos()
//{
//	VerifyPos_Msg msg;
//	msg.type = M_VerifyPos;
//	msg.x = PlayerPos.x;
//	msg.y = PlayerPos.y;
//	msg.fd = -1;
//	SendMsg((char*)&msg, sizeof(msg));
//}

//void SocketManager::updatePlayerData()
//{
//	UpdateData_Msg msg;
//	msg.type = M_UpdateData;
//	msg.attack = GetPlayerData().getattack();
//	msg.blood = GetPlayerData().getblood();
//	msg.defense = GetPlayerData().getdefense();
//	msg.fd = -1;
//	msg.grade = GetPlayerData().getgrade();
//	msg.mana = GetPlayerData().getmana();
//	SendMsg((char*)&msg, sizeof(msg));
//}

//void SocketManager::doPlayerDataUpdaeMsg(UpdateData_Msg* msg)
//{
//	for (auto var =m_playerlist.begin();var!=m_playerlist.end();++var)
//	{
//		if (var->fd == msg->fd)
//		{
//			var->attack = msg->attack;
//			var->defense = msg->defense;
//			var->blood = msg->blood;
//			var->grade=msg->grade;
//			var->mana = msg->mana;
//			//if (Director::getInstance()->getRunningScene()->getChildByName("ObjectLayer") != nullptr)
//				//CurGameScene()->getObjectLayer()->updatePlayerData(var->playername, var->rolename, *msg);
//		}
//	}
//}
//
//std::string SocketManager::findRoleNameByFd(const int& fd)
//{
//	for(auto var:m_playerlist)
//	{
//		if (var.fd == fd)
//		{
//			return var.rolename;
//		}
//	}
//	return "";
//}

//void SocketManager::addWorldTalkMsg(WorldTalk_Msg* msg)
//{
//	//TalkMsg tmsg;
//	//if (msg->fd != -1)
//	//	tmsg.rolename = findRoleNameByFd(msg->fd);
//	//else
//	//	tmsg.rolename = StringValue("Me");
//	//tmsg.msg = msg->msg;
//	//m_worldTalkMsgs.push_back(tmsg);
//	//if (m_worldTalkMsgs.size() > 100)
//	//{
//	//	m_worldTalkMsgs.pop_front();
//	//}
//	//if (GetIntData("IsHaveGameScene") == 1)
//	//	CurGameScene()->getGameUiLayer()->updateWorldTalkQueue(tmsg);
//}

//void SocketManager::addPrivateTalkMsg(PrivateTalk_Msg* msg)
//{
//	//TalkMsg tmsg;
//	//int realfd;
//	//if (msg->fd != -1)
//	//{
//	//	tmsg.rolename = findRoleNameByFd(msg->fd);
//	//	realfd = msg->fd;
//	//}
//	//else
//	//{
//	//	tmsg.rolename = StringValue("Me");
//	//	realfd = msg->dest;
//	//}
//	//tmsg.destname = findRoleNameByFd(realfd);
//	//if (tmsg.destname == "")
//	//{
//	//	SetIntData("IsHaveTip", 1);
//	//	SetStringData("TipText", StringValue("OffLine"));
//	//	return;
//	//}
//	//tmsg.msg = msg->msg;
//	//if (m_privateTalkMsgs.find(realfd) != m_privateTalkMsgs.end())
//	//{
//	//	if (m_privateTalkMsgs.size() >= 6)
//	//		m_privateTalkMsgs.erase(m_privateTalkMsgs.begin());
//	//}
//	//m_privateTalkMsgs[realfd].push_back(tmsg);
//	//if (GetIntData("IsHaveGameScene") == 1)
//	//{
//	//	PrivateTalkLayer* ptlayer = (PrivateTalkLayer*)CurGameScene()->getChildByName("PrivateTalkLayer");
//	//	if (ptlayer != nullptr)
//	//		ptlayer->addMsg(tmsg.rolename, tmsg.msg);
//	//}
//	//if (msg->fd != -1)
//	//{
//	//	m_privateTalkMsgs[realfd][0].change = true;
//	//	if (GetIntData("IsHaveGameScene") == 1)
//	//		CurGameScene()->getGameUiLayer()->setRedSpot(true);
//	//}
//	//if (m_privateTalkMsgs[realfd].size() >18)
//	//{
//	//	m_privateTalkMsgs[realfd].pop_front();
//	//}
//}
//
//Player_Info SocketManager::findPlayerInfoByFd(const int& fd)
//{
//	Player_Info info;
//	for (const auto& var : m_playerlist)
//	{
//		if (var.fd == fd)
//		{
//			return var;
//		}
//	}
//	return info;
//}

//void SocketManager::doTeamApplyMsg(TeamApply_Msg* msg)
//{
//	m_applyTeamList.push_back(msg->fd);
//	if (m_applyTeamList.size() > 6)
//	{
//		m_applyTeamList.pop_front();
//	}
//	if (GetIntData("IsHaveGameScene") == 1)
//	{
//		CurGameScene()->getGameUiLayer()->setTeamSpot(true);
//	}
//}

//void SocketManager::doRefuseTeamMsg(RefuseTeam_Msg* msg)
//{
//	std::string name = findRoleNameByFd(msg->fd);
//	SetIntData("IsHaveTip", 1);
//	SetStringData("TipText", name + StringValue("RefuseText"));
//}

//void SocketManager::doAgreeTeamMsg(AgreeTeam_Msg* msg)
//{
//	std::string name = findRoleNameByFd(msg->fd);
//	SetIntData("IsHaveTip", 1);
//	SetStringData("TipText",name + StringValue("AgreeText"));
//	CameraPlayer::getPlayerInstance()->setTeamStatus(P_STATUS_HEADER);
//	TeamManager::getInstance()->createTeam(msg->fd, P_STATUS_MEMBER);
//}

//void SocketManager::sendTeamMoveMsg(cocos2d::Vec2 target, int dest)
//{
//	TeamMove_Msg msg;
//	msg.x = target.x;
//	msg.y = target.y;
//	msg.dest = dest;
//	SendMsg((char*)&msg, sizeof(msg));
//}
//
//void SocketManager::doTeamMoveMsg(TeamMove_Msg* msg)
//{
//	CameraPlayer::getPlayerInstance()->moveTo(Vec2{ msg->x,msg->y }, 1);
//}

//void SocketManager::sendTeamGotoMapMsg(std::string map, cocos2d::Vec2 target, int dest)
//{
//	TeamGotoMap msg;
//	msg.dest = dest;
//	strcpy_s(msg.map, map.c_str());
//	msg.x = target.x;
//	msg.y = target.y;
//	SendMsg((char*)&msg, sizeof(msg));
//}

//void SocketManager::doTeamGotoMapMsg(TeamGotoMap* msg)
//{
//	if (CCDirector::getInstance()->getRunningScene()->getName() == "GameScene")
//		m_gotoMapMsgs.push_back(*msg);
//}

//void SocketManager::SendTeamDissolveMsg(int dest)
//{
//	TeamManage_Msg msg;
//	msg.type = M_DissolveTeam;
//	msg.dest = dest;
//	SendMsg((char*)&msg, sizeof(msg));
//}

//void SocketManager::doTeamDissolveMsg()
//{
//	TeamManager::getInstance()->dissolveTeam();
//	SetIntData("IsHaveTip", 1);
//	SetStringData("TipText", StringValue("TeamDissolveText"));
//}

//void SocketManager::sendTeamFightMsg(int dest, std::string name, int nums)
//{
//	TeamFight_Msg msg;
//	msg.dest = dest;
//	strcpy_s(msg.name, name.c_str());
//	msg.nums = nums;
//	SendMsg((char*)&msg, sizeof(msg));
//}

//void SocketManager::doTeamFightMsg(TeamFight_Msg* msg)
//{
//	if (Director::getInstance()->getRunningScene()->getName() == "GameScene")
//	{
//		SetIntData("IsEntryFight", 1);
//		SetIntData("MonsterNums", msg->nums);
//		SetStringData("MonsterName", msg->name);
//	}
//}

//void SocketManager::sendPlayerAtkMsg(std::string skill, int grade,int dest, int towho)
//{
//	PlayerAtk_Msg msg;
//	msg.fd = -1;
//	msg.grade = grade;
//	msg.dest = dest;
//	strcpy_s(msg.skill, skill.c_str());
//	msg.towho = towho;
//	SendMsg((char*)&msg, sizeof(msg));
//}

//void SocketManager::sendMonsterAtkMsg(int dest, int who, int towho)
//{
//	MonsterAtk_Msg msg;
//	msg.dest = dest;
//	msg.fd = -1;
//	msg.who = who;
//	msg.towho = towho;
//	SendMsg((char*)&msg, sizeof(msg));
//}

//void SocketManager::doPlayerAtkMsg(PlayerAtk_Msg* msg)
//{
//	auto ftLayer = Director::getInstance()->getRunningScene()->getChildByName("FightLayer");
//	if (ftLayer != nullptr)
//	{
//		((FightLayer*)ftLayer)->otherPlayerAtk(msg->fd, msg->skill, msg->grade, msg->towho);
//	}
//}

//void SocketManager::doMonsterAtkMsg(MonsterAtk_Msg* msg)
//{
//	auto ftLayer = Director::getInstance()->getRunningScene()->getChildByName("FightLayer");
//	if (ftLayer != nullptr)
//	{
//		int towho;
//		if (msg->towho == -1)
//		{
//			towho = ((FightLayer*)ftLayer)->findOtherPlayerIndexByFd(msg->fd);
//		}
//		else
//		{
//			towho = ((FightLayer*)ftLayer)->findOtherPlayerIndexByFd(msg->towho);
//		}
//		((FightLayer*)ftLayer)->monsterAttackPlayer(msg->who, towho);
//	}
//}
//
//void SocketManager::sendPlayerRunMsg(int dest,int flag)
//{
//	PlayerRun_Msg msg;
//	msg.dest = dest;
//	msg.flag = flag;
//	SendMsg((char*)&msg, sizeof(msg));
//}

//void SocketManager::doPlayerRunMsg(PlayerRun_Msg* msg)
//{
//	auto ftLayer = Director::getInstance()->getRunningScene()->getChildByName("FightLayer");
//	if (ftLayer != nullptr)
//	{
//		dynamic_cast<FightLayer*>(ftLayer)->OtherRunAway(msg->flag);
//	}
//}

//void SocketManager::sendUseMedicationMsg(int dest)
//{
//	UseMedication_Msg msg;
//	msg.dest = dest;
//	SendMsg((char*)&msg, sizeof(msg));
//}

//void SocketManager::doUseMedicationMsg(UseMedication_Msg* msg)
//{
//	auto ftLayer = Director::getInstance()->getRunningScene()->getChildByName("FightLayer");
//	if (ftLayer != nullptr)
//		dynamic_cast<FightLayer*>(ftLayer)->setOtherPalyerEnd();
//}
//
//void SocketManager::sendPlayerDieMsg(int dest)
//{
//	PlayerDie_Msg msg;
//	msg.dest = dest;
//	SendMsg((char*)&msg, sizeof(msg));
//}

//void SocketManager::doPlayerDieMsg(PlayerDie_Msg* msg)
//{
//	auto ftLayer = Director::getInstance()->getRunningScene()->getChildByName("FightLayer");
//	if (ftLayer != nullptr)
//		dynamic_cast<FightLayer*>(ftLayer)->setOtherPlayerDie();
//}
