#include"NetWorkManager.h"
#include"SocketManager.h"
#include"jsonCpp/value.h"
using namespace Json;

DEFINE_SINGLE_ATTRIBUTES(NetWorkManager);

Slot* NetWorkManager::add(const int & messageId, const EventHandler& evHandler)
{
	Signal signal = m_signals[messageId];
	return signal.add(evHandler);
}

Slot * NetWorkManager::add(const int & messageId, const std::function<void(Json::Value&)>& func)
{
	Signal signal = m_signals[messageId];
	return signal.add(func);
}

void NetWorkManager::dispatch(const int & messageId,Json::Value& message)
{
	m_signals[messageId].dispatch(message);
}

void NetWorkManager::send(const int & messageId, const std::map<std::string, std::string>& msg)
{
	Json::Value value;
	value["MessageId"] = messageId;
	for (auto var : msg)
	{
		value[var.first] = var.second;
	}
	std::string out = value.toStyledString();
	SocketManager::getInstance()->SendMsg(out.c_str(), out.length());
}
