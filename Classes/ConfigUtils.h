#pragma once
#ifndef __CONFIG_UATILS_H__
#define __CONFIG_UATILS_H__
#include"PreProcess.h"
#include<vector>
#include<map>

#define CONFIG_NAME 0

class ConfigUtils
{
	GET_SINGLE_OBJECT(ConfigUtils)
public:
	std::map<std::string, std::string> getConfigAttr(const std::string& pathname);

	std::vector<std::string> getConfigDec(const std::string& pathname);

	void getConfigDrop(const std::string& pathname);

	std::vector<std::string> split(std::string& str, std::string& part);
private:
	ConfigUtils() {}

	SINGLE_ATTRIBUTES(ConfigUtils);
};

#endif // !__CONFIG_UATILS_H__

