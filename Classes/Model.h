#pragma once
#ifndef __MODEL_H__
#define __MODEL_H__
#include<string>

#define GettingAndSetting_S(varType,varName,funName) \
private: varType varName=""; \
public: varType& get##funName(void){return varName;} \
public: void set##funName(const varType& var) {varName=var;}

class GamePlayer
{
public:
	GamePlayer() {}
	~GamePlayer() {}

	GettingAndSetting_S(std::string, playerName, playerName);
	GettingAndSetting_S(std::string, playerPsw, playerPsw);
	GettingAndSetting_S(std::string, nums, nums);
public:
	std::string& operator[](const int& index)
	{
		switch (index)
		{
		case 1:
			return playerName;
		case 2:
			return playerPsw;
		case 3:
			return nums;
		default:
			return playerName;
			break;
		}
	}

	std::string getAttributeName(const int& index)
	{
		switch (index)
		{
		case 1:
			return "playername";
		case 2:
			return "playerpsw";
		case 3:
			return "nums";
		default:
			break;
		}
		return "";
	}
	
	std::string getName()
	{
		return "player";
	}

	int getAttributeNums()
	{
		return 3;
	}
};

class PlayerInfo
{
public:
	PlayerInfo() {}
	~PlayerInfo() {}

	GettingAndSetting_S(std::string, playerName, playerName);
	GettingAndSetting_S(std::string, roleName, roleName);
	GettingAndSetting_S(std::string, roleType, roleType);
	GettingAndSetting_S(std::string, glod, glod);
	GettingAndSetting_S(std::string, grade, grade);
	GettingAndSetting_S(std::string, blood, blood);
	GettingAndSetting_S(std::string, mana, mana);
	GettingAndSetting_S(std::string, attack, attack);
	GettingAndSetting_S(std::string, defense, defense);
	GettingAndSetting_S(std::string, speed, speed);
	GettingAndSetting_S(std::string, exp, exp);
	GettingAndSetting_S(std::string, maxExp, maxExp);
	GettingAndSetting_S(std::string, destx, destx);
	GettingAndSetting_S(std::string, desty, desty);
	GettingAndSetting_S(std::string, level, level);
	GettingAndSetting_S(std::string, sect, sect);
public:
	std::string& operator[](const int& index)
	{
		switch (index)
		{
		case 1:
			return playerName;
		case 2:
			return roleName;
		case 3:
			return roleType;
		case 4:
			return glod;
		case 5:
			return grade;
		case 6:
			return blood;
		case 7:
			return mana;
		case 8:
			return attack;
		case 9:
			return defense;
		case 10:
			return speed;
		case 11:
			return exp;
		case 12:
			return maxExp;
		case 13:
			return destx;
		case 14:
			return desty;
		case 15:
			return level;
		case 16:
			return sect;
		default:
			return playerName;
			break;
		}
	}
	
	std::string getAttributeName(const int& index)
	{
		switch (index)
		{
		case 1:
			return "playername";
		case 2:
			return "rolename";
		case 3:
			return "roletype";
		case 4:
			return "glod";
		case 5:
			return "grade";
		case 6:
			return "blood";
		case 7:
			return "mana";
		case 8:
			return "attack";
		case 9:
			return "defense";
		case 10:
			return "speed";
		case 11:
			return "exp";
		case 12:
			return "maxexp";
		case 13:
			return "destx";
		case 14:
			return "desty";
		case 15:
			return "level";
		case 16:
			return "sect";
		default:
			break;
		}
		return "";
	}

	std::string getName()
	{
		return "playerinfo";
	}
	
	int getAttributeNums()
	{
		return 16;
	}
};

class SkillInfo 
{
public:
	SkillInfo() {}
	~SkillInfo() {}

	GettingAndSetting_S(std::string, playername, playername);
	GettingAndSetting_S(std::string, rolename, rolename);
	GettingAndSetting_S(std::string, skillname, skillname);
	GettingAndSetting_S(std::string, skillgrade, skillgrade);
public:
	std::string& operator[](const int& index)
	{
		switch (index)
		{
		case 1:
			return playername;
		case 2:
			return rolename;
		case 3:
			return skillname;
		case 4:
			return skillgrade;
		default:
			return playername;
		}
	}

	std::string getAttributeName(const int& index)
	{
		switch (index)
		{
		case 1:
			return "playername";
		case 2:
			return "rolename";
		case 3:
			return "skillname";
			break;
		case 4:
			return "skillgrade";
		default:
			return "playername";
		}
	}

	std::string getName()
	{
		return "skillinfo";
	}

	int getAttributeNums()
	{
		return 4;
	}
};

class EquipmentInfo
{
public:
	EquipmentInfo() {}
	~EquipmentInfo() {}
	GettingAndSetting_S(std::string, playername, playername);
	GettingAndSetting_S(std::string, rolename, rolename);
	GettingAndSetting_S(std::string, equipmentname, equipmentname);
	GettingAndSetting_S(std::string, grade, grade);
	GettingAndSetting_S(std::string, type, type);
public:
	std::string& operator[](const int& index)
	{
		switch (index)
		{
		case 1:
			return playername;
		case 2:
			return rolename;
		case 3:
			return equipmentname;
		case 4:
			return grade;
		case 5:
			return type;
		default:
			return playername;
		}
	}

	std::string getAttributeName(const int& index)
	{
		switch (index)
		{
		case 1:
			return "playername";
		case 2:
			return "rolename";
		case 3:
			return "equipmentname";
			break;
		case 4:
			return "grade";
		case 5:
			return "type";
		default:
			return "playername";
		}
	}

	std::string getName()
	{
		return "equipmentinfo";
	}

	int getAttributeNums()
	{
		return 5;
	}
};

class BackPack
{
public:
	BackPack() {}
	~BackPack() {}
	GettingAndSetting_S(std::string, playername, playername);
	GettingAndSetting_S(std::string, rolename, rolename);
	GettingAndSetting_S(std::string, thingname, thingname);
	GettingAndSetting_S(std::string, thingtype, thingtype);
	GettingAndSetting_S(std::string, thingnums, thingnums);
	GettingAndSetting_S(std::string, thinggrade, thinggrade);
public:
	std::string& operator[](const int& index)
	{
		switch (index)
		{
		case 1:
			return playername;
		case 2:
			return rolename;
		case 3:
			return thingname;
		case 4:
			return thingtype;
		case 5:
			return thingnums;
		case 6:
			return thinggrade;
		default:
			return playername;
		}
	}

	std::string getAttributeName(const int& index)
	{
		switch (index)
		{
		case 1:
			return "playername";
		case 2:
			return "rolename";
		case 3:
			return "thingname";
			break;
		case 4:
			return "thingtype";
		case 5:
			return "thingnums";
		case 6:
			return "thinggrade";
		default:
			return "playername";
		}
	}

	std::string getName()
	{
		return "backpack";
	}

	int getAttributeNums()
	{
		return 6;
	}
};

class Friend
{
public:
	Friend() {}
	~Friend() {}
	GettingAndSetting_S(std::string, playername, playername);
	GettingAndSetting_S(std::string, rolename, rolename);
	GettingAndSetting_S(std::string, friendpname, friendpname);
	GettingAndSetting_S(std::string, friendrname, friendrname);
	GettingAndSetting_S(std::string, friendrtype, friendrtype);
	GettingAndSetting_S(std::string, friendgrade, friendgrade);
public:
	std::string& operator[](const int& index)
	{
		switch (index)
		{
		case 1:
			return playername;
		case 2:
			return rolename;
		case 3:
			return friendpname;
		case 4:
			return friendrname;
		case 5:
			return friendrtype;
		case 6:
			return friendgrade;
		default:
			return playername;
		}
	}

	std::string getAttributeName(const int& index)
	{
		switch (index)
		{
		case 1:
			return "playername";
		case 2:
			return "rolename";
		case 3:
			return "friendpname";
			break;
		case 4:
			return "friendrname";
		case 5:
			return "friendrtype";
		case 6:
			return "friendgrade";
		default:
			return "playername";
		}
	}

	std::string getName()
	{
		return "friend";
	}

	int getAttributeNums()
	{
		return 6;
	}
};

class Playermw
{
public:
	Playermw() {}
	~Playermw() {}
	GettingAndSetting_S(std::string, playername, playername);
	GettingAndSetting_S(std::string, rolename, rolename);
	GettingAndSetting_S(std::string, mw_name, mw_name);
	GettingAndSetting_S(std::string, grade, grade);
	GettingAndSetting_S(std::string, curexp, curexp);
	GettingAndSetting_S(std::string, exp, exp);
	GettingAndSetting_S(std::string, is_in_battle, Is_in_battle);
public:
	std::string& operator[](const int& index)
	{
		switch (index)
		{
		case 1:
			return playername;
		case 2:
			return rolename;
		case 3:
			return mw_name;
		case 4:
			return grade;
		case 5:
			return curexp;
		case 6:
			return exp;
		case 7:
			return is_in_battle;
		default:
			return playername;
		}
	}

	std::string getAttributeName(const int& index)
	{
		switch (index)
		{
		case 1:
			return "playername";
		case 2:
			return "rolename";
		case 3:
			return "mw_name";
		case 4:
			return "grade";
		case 5:
			return "curexp";
		case 6:
			return "exp";
		case 7:
			return "is_in_battle";
		default:
			return "playername";
		}
	}

	std::string getName()
	{
		return "playermw";
	}

	int getAttributeNums()
	{
		return 7;
	}
};

#endif // !__MODEL_H__