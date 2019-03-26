#include "Path.h"

std::string getButtonPath(std::string id)
{
	return std::string("button/") + id + PNG;
}

std::string getBackgroundPath(std::string id)
{
	return std::string("Background/") + id + PNG;
}

std::string getTalismanPath(std::string id)
{
	return std::string("talisman/") + id + PNG;
}

std::string getTalismanPurePath(std::string id)
{
	return std::string("talisman/") + id;
}

std::string getMainPath(std::string id)
{
	return id + PNG;
}

std::string getFontPath(std::string id)
{
	return std::string("res/font/") + id + TTF;
}

std::string getMonsterPath(std::string id)
{
	return std::string("Monster/") + id + std::string("/") + id;
}

std::string getCommonPath(std::string id)
{
	return std::string("Common/") + id + PNG;
}

std::string getSectUIPath(std::string id)
{
	return std::string("Sect/UI/") + id + PNG;
}

std::string getSectPath(std::string id)
{
	return std::string("Sect/") + id;
}

std::string getSectBgPath(std::string id)
{
	return std::string("Sect/UI/") + id + std::string("_bg") + JPG;
}

std::string getPlayerWaitPath(std::string type, std::string id)
{
	return type + std::string("/wait/") + id;
}
