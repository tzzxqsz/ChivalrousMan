#include"ConfigUtils.h"
#include<fstream>
#include<regex>
DEFINE_SINGLE_ATTRIBUTES(ConfigUtils);

std::map<std::string, std::string>  ConfigUtils::getConfigAttr(const std::string& pathname)
{
	std::map<std::string, std::string> attrmaps;
	std::string realname = pathname;
	realname += ".attr";
	std::ifstream fin;
	fin.open(realname, std::ios::in);
	if (fin.fail())
	{
		return attrmaps;
	}
	std::string tmp;
	fin >> tmp;
	attrmaps["textname"] = tmp;
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

std::map<std::string, std::vector<std::string>> ConfigUtils::getConfigDrop(const std::string & pathname)
{
	std::map<std::string, std::vector<std::string>> ret;
	std::string realname = pathname + ".dp";
	std::ifstream fin;
	fin.open(realname, std::ios::in);
	if (fin.fail())
	{
		return ret;
	}
	std::string type;
	std::string name;
	std::string percent;
	std::string value;
	fin >> type;
	fin >> value;
	ret[type].push_back(value);
	fin >> name;
	fin >> value;
	value.replace(value.find("{"), 1, "");
	value.replace(value.find("}"), 1, "");
	ret[name] = split(value, std::string(","));
	fin >> percent;
	fin >> value;
	value.replace(value.find("{"), 1, "");
	value.replace(value.find("}"), 1, "");
	ret[percent] = split(value, std::string(","));
	fin.close();
	return ret;
}

std::vector<std::string> ConfigUtils::split(std::string & str, std::string & part)
{
	std::vector<std::string> ret;
	std::regex r4((std::string("\\s*[") + part + std::string("]\\s*")));
	const std::sregex_token_iterator send;
	for (std::sregex_token_iterator iter(str.cbegin(), str.cend(), r4, -1); iter != send; ++iter)
	{
		ret.push_back(*iter);
	}
	return ret;
}
