#pragma once
#ifndef SHAREDATA_H
#define SHAREDATA_H
#include<string>

struct Player_Info
{
	std::string playername;
	std::string rolename;
	float blood;
	float mana;
	float attack;
	float defense;
	int curmap;
	std::string playertype;
	float x;
	float y;
	int grade;
	int fd;

	Player_Info()
	{
		fd = -1;
	}
};

struct TeamGotoMap
{
	std::string map;
	float x;
	float y;
	int dest;
};

#endif // SHAREDATA_H