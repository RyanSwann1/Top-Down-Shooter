#pragma once

#include <functional>
#include <unordered_map>
#include <Game\GlobalMessage.h>

class GlobalMessenger
{
public:
	GlobalMessenger();
	GlobalMessenger(const GlobalMessenger&) = delete;
	GlobalMessenger& operator=(const GlobalMessenger&) = delete;
	GlobalMessenger(GlobalMessenger&&) = delete;
	GlobalMessenger&& operator=(GlobalMessenger&&) = delete;

	void addMessage(GlobalMessage message, std::function<void()>&& fp);
	void removeMessage(GlobalMessage message);
	void activateMessage(GlobalMessage message) const;

private:
	std::unordered_map<GlobalMessage, std::function<void()>> m_messages;
};