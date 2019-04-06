#include"SectManager.h"
#include"DBDao.h"
#include"Model.h"
#include"CameraPlayer.h"
#include"UIHelper.h"
#include"ConfigUtils.h"
#include"GameData.h"
#include"Path.h"
#include<map>

DEFINE_SINGLE_ATTRIBUTES(SectManager);

bool SectManager::joinSect(const std::string & name)
{
	DBDao<PlayerInfo> db;
	PlayerInfo pi;
	pi.setsect(name);
	db.setModel(pi); 
	std::map<std::string, std::string> kvls;
	kvls["playername"] = GetPlayerData().getplayername();
	kvls["rolename"] = GetPlayerData().getrolename();
	return db.updateModel(kvls);
 }

void SectManager::learnGongfa(const std::string & name)
{
	if (!haveLearned(name))
	{
		auto dec = ConfigUtils::getInstance()->getConfigAttr(getSectSkillAttrPath(GetPlayerData().getSect(), name));
		float gold = std::stof(dec["gold"]);
		if (GetPlayerData().getglod() >= gold)
		{
			DBDao<PlayerGongfa> db;
			PlayerGongfa md;
			md.setplayername(GetPlayerData().getplayername());
			md.setrolename(GetPlayerData().getrolename());
			md.setname(name);
			db.setModel(md);
			if (db.insertModel())
			{
				UIHelper::getInstance()->showTip(StringValue("SuccessLearnedGongfa"));
				m_gongfas.push_back(name);
				GetPlayerData().subGlod(gold);
			}
			db.close();
		}
		else
		{
			UIHelper::getInstance()->showTip(StringValue("LackGlod"));
		}
	}
	else
	{
		UIHelper::getInstance()->showTip(StringValue("HavedLeand"));
	}
}

std::string SectManager::getGongfa()
{
	if (!m_gongfas.empty())
	{
		return m_gongfas.back();
	}
	return std::string("");
}

Jingjie SectManager::getJingjie()
{
	return m_jingjie;
}

std::string SectManager::getJingjieName()
{
	auto decs = ConfigUtils::getInstance()->getConfigDec(getSectPath("XiulianJingjie"));
	return decs[m_jingjie.name == -1 ? 0 : m_jingjie.name];
}

std::string SectManager::getGongfaName()
{
	auto name = getGongfa();
	if (name != "")
	{
		auto decs = ConfigUtils::getInstance()->getConfigAttr(getSectSkillAttrPath(GetPlayerData().getSect(), name));
		return decs["textname"];
	}
	return std::string("");
}

bool SectManager::addXiulianExp(float exp)
{
	int last = m_jingjie.name;
	if (last == -1)
	{
		m_jingjie.name = 0;
	}
	addXiulianExpEx(exp);
	DBDao<PlayerJingjie> db;
	PlayerJingjie md;
	md.setjingjie(NTS(m_jingjie.name));
	md.setcurexp(NTS(m_jingjie.curexp));
	md.setexp(NTS(m_jingjie.exp));
	if (last == -1)
	{
		md.setplayername(GetPlayerData().getplayername());
		md.setrolename(GetPlayerData().getrolename());
		db.setModel(md);
		return db.insertModel();
	}
	else
	{
		std::map<std::string, std::string> kvls;
		kvls["playername"] = GetPlayerData().getplayername();
		kvls["rolename"] = GetPlayerData().getrolename();
		db.setModel(md);
		return db.updateModel(kvls);
	}
}

SectManager::SectManager()
{
	initData();
}

SectManager::~SectManager()
{
}

void SectManager::addXiulianExpEx(float exp)
{
	m_jingjie.curexp += exp;
	if (m_jingjie.curexp >= m_jingjie.exp)
	{
		float sunexp = m_jingjie.curexp - m_jingjie.exp;
		++m_jingjie.name;
		m_jingjie.curexp = 0;
		m_jingjie.exp = m_jingjie.exp + (m_jingjie.name)*m_jingjie.exp;
		addXiulianExpEx(sunexp);
	}
}

bool SectManager::haveLearned(const std::string & name)
{
	if (true)
	{
		return !m_gongfas.empty();
	}
	else
	{
		for (auto& gongfa : m_gongfas)
		{
			if (gongfa == name)
			{
				return true;
			}
		}
		return false;
	}
}

void SectManager::initData()
{
	DBDao<PlayerGongfa> db;
	PlayerGongfa pgf;
	pgf.setplayername(GetPlayerData().getplayername());
	pgf.setrolename(GetPlayerData().getrolename());
	db.setModel(pgf);
	auto gongfas = db.queryModel();
	for (auto& var : gongfas)
	{
		m_gongfas.push_back(var.getname());
	}
	db.close();
	DBDao<PlayerJingjie> db1;
	PlayerJingjie pjj;
	pjj.setplayername(GetPlayerData().getplayername());
	pjj.setrolename(GetPlayerData().getrolename());
	auto jj = db1.queryModel();
	if (!jj.empty())
	{
		m_jingjie.name = std::stoi(jj[0].getjingjie());
		m_jingjie.curexp = std::stof(jj[0].getcurexp());
		m_jingjie.exp = std::stof(jj[0].getexp());
	}
	db1.close();
}
