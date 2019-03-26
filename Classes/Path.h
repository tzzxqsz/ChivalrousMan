#pragma once
#ifndef __PATH_H__
#define __PATH_H__
#include<string>

static const std::string PNG = ".png";
static const std::string JPG = ".jpg";
static const std::string TTF = ".ttf";

std::string getButtonPath(std::string id);

std::string getBackgroundPath(std::string id);

std::string getTalismanPath(std::string id);

std::string getTalismanPurePath(std::string id);

std::string getMainPath(std::string id);

std::string getFontPath(std::string id);

std::string getMonsterPath(std::string id);

std::string getCommonPath(std::string id);

std::string getSectUIPath(std::string id);

std::string getSectPath(std::string id);

std::string getSectBgPath(std::string id);

std::string getPlayerWaitPath(std::string type, std::string id);


#endif // !1

