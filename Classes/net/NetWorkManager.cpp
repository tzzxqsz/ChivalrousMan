#include"NetWorkManager.h"
#include"SocketManager.h"
#include"jsonCpp/value.h"
#include"tool/LogUtil.h"
#include"tool/GameData.h"
using namespace Json;

DEFINE_SINGLE_ATTRIBUTES(NetWorkManager);

Slot* NetWorkManager::add(const int & messageId, const EventHandler& evHandler)
{
	if (m_signals.find(messageId) != m_signals.end())
		return m_signals[messageId].add(evHandler);
	else
	{
		m_signals[messageId] = Signal();
		return m_signals[messageId].add(evHandler);
	}
}

Slot * NetWorkManager::add(const int & messageId, const std::function<void(Json::Value&)>& func)
{
	if (m_signals.find(messageId) != m_signals.end())
		return m_signals[messageId].add(func);
	else
	{
		m_signals[messageId] = Signal();
		return m_signals[messageId].add(func);
	}
}

void NetWorkManager::dispatch(const int & messageId,Json::Value& message)
{
	LOG("dispatch:");
	LOG(message);
	m_signals[messageId].dispatch(message);
}

void NetWorkManager::send(const int & messageId, const std::map<std::string, std::string>& msg)
{
	Json::Value value;
	value["MessageId"] = messageId;
	for (auto var : msg)
	{
		if (IS_NUM(var.second))
			value[var.first] = std::stof(var.second);
		else
			value[var.first] = var.second;
	}
	std::string out = value.toStyledString();
	SocketManager::getInstance()->SendMsg(out.c_str(), out.length());
}

void NetWorkManager::send(const int & messageId, Json::Value & msg)
{
	msg["MessageId"] = messageId;
	std::string out = msg.toStyledString();
	SocketManager::getInstance()->SendMsg(out.c_str(), out.length());
	LOG("send:");
	LOG(msg);
}
