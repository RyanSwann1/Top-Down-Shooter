#include <Game\GlobalMessenger.h>
#include <Locators\GlobalMessengerLocator.h>
#include <assert.h>
#include <algorithm>
#include <utility>

GlobalMessenger::GlobalMessenger()
	: m_messages()
{
	GlobalMessengerLocator::provide(*this);
}

void GlobalMessenger::addMessage(GlobalMessage message, std::function<void()>&& fp)
{
	assert(m_messages.find(message) == m_messages.cend());
	m_messages.emplace(message, std::move(fp));
}

void GlobalMessenger::removeMessage(GlobalMessage message)
{
	auto iter = m_messages.find(message);
	assert(iter != m_messages.cend());
	m_messages.erase(iter);
}

void GlobalMessenger::activateMessage(GlobalMessage message) const
{
	auto iter = m_messages.find(message);
	assert(iter != m_messages.cend());
	iter->second();
}
