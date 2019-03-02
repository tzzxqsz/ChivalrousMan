#include "SignalManager.h"

DEFINE_SINGLE_ATTRIBUTES(SignalManager);

SignalManager::SignalManager()
{
	
}

SignalManager::~SignalManager()
{
}

Slot* SignalManager::add(const int& messageId, const EventHandler& evHandler, const bool& once)
{
	if (m_signals.find(messageId) == m_signals.end())
		m_signals[messageId] = Signal();
	if (!once)
		return m_signals[messageId].add(evHandler);
	else
		return m_signals[messageId].addOnce(evHandler);
}

Slot * SignalManager::add(const int & messageId, const std::function<void(Json::Value&)>& func, const bool & once)
{
	if (m_signals.find(messageId) == m_signals.end())
		m_signals[messageId] = Signal();
	if (!once)
		return m_signals[messageId].add(func);
	else
		return m_signals[messageId].addOnce(func);
}

void SignalManager::dispatch(const int & messageId, Json::Value & message)
{
	if (m_signals.find(messageId) != m_signals.end())
		m_signals[messageId].dispatch(message);
}