#include"LogUtil.h"

DEFINE_SINGLE_ATTRIBUTES(LogUtil);

LogUtil::LogUtil()
{
	m_log.open("game.log");
}

LogUtil::~LogUtil()
{
	m_log.close();
}

int LogUtil::log(const char* content)
{
	m_log << content << std::endl;
	m_log.flush();
	return 0;
}

int LogUtil::log(const std::string& content)
{
	m_log << content << std::endl;
	m_log.flush();
	return 0;
}

int LogUtil::log(const Json::Value & value)
{
	m_log << value.toStyledString();
	m_log.flush();
	return 0;
}
