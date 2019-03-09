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

std::string getMainPath(std::string id)
{
	return id + PNG;
}

std::string getFontPath(std::string id)
{
	return std::string("res/font/") + id + TTF;
}
