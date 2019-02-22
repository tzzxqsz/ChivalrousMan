#pragma once
#ifndef __LOG_UTIL_H__
#define __LOG_UTIL_H__
#include"PreProcess.h"
#include<fstream>
#include"jsonCpp/value.h"

#define LOG LogUtil::getInstance()->log

class LogUtil
{
	GET_SINGLE_OBJECT(LogUtil)
public:
	int log(const char* content);

	int log(const std::string& content);

	int log(const Json::Value& value);
private:
	LogUtil();
	~LogUtil();

	std::ofstream m_log;

	SINGLE_ATTRIBUTES(LogUtil);
};

#endif // !__LOG_UTIL_H__

