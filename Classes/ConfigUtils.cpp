#include"ConfigUtils.h"
#include<fstream>

DEFINE_SINGLE_ATTRIBUTES(ConfigUtils);

std::map<std::string, std::string>  ConfigUtils::getConfigAttr(const std::string& pathname)
{
	std::map<std::string, std::string> attrmaps;
	std::string realname = pathname;
	realname += ".att";
	std::ifstream fin;
	fin.open(realname, std::ios::in);
	if (fin.fail())
	{
		return attrmaps;
	}
	std::string tmp;
	fin >> tmp;
	std::string name;
	std::string value;
	while (!fin.eof())
	{
		fin >> name;
		fin >> value;
		if (name == "" || value == "")
			continue;
		attrmaps[name] = value;
		name = "";
		value = "";
	}
	fin.close();
	return attrmaps;
}

std::vector<std::string> ConfigUtils::getConfigDec(const std::string & pathname)
{
	std::vector<std::string> dec;
	std::string realname = pathname;
	realname += ".dec";
	std::ifstream fin;
	fin.open(realname, std::ios::in);
	if (fin.fail())
	{
		return dec;
	}
	std::string tmp;
	while (!fin.eof())
	{
		fin >> tmp;
		if (tmp == "")
			continue;
		dec.push_back(tmp);
		tmp = "";
	}
	fin.close();
	return dec;
}
