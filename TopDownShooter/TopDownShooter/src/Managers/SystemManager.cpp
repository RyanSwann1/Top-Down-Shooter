#include <Managers\SystemManager.h>
#include <algorithm>
#include <Systems\SystemDrawable.h>
#include <Systems\SystemMovable.h>
#include <Systems\SystemPlayerController.h>
#include <assert.h>

//System Factory
SystemManager::SystemFactory::SystemFactory(SystemManager* systemManager)
{
	registerSystem<SystemDrawable>(systemManager, SystemType::Drawable);
	registerSystem<SystemMovable>(systemManager, SystemType::Movable);
	registerSystem<SystemPlayerController>(systemManager, SystemType::PlayerController);
}

std::unique_ptr<SystemBase> SystemManager::SystemFactory::getSystem(SystemType type) const
{
	auto iter = m_systemFactory.find(type);
	assert(iter != m_systemFactory.cend());
	return iter->second();
}

//System Manager
SystemManager::SystemManager()
	: m_systemFactory(this),
	m_systems()
{
	addSystem(SystemType::Drawable);
	addSystem(SystemType::Movable);
	addSystem(SystemType::PlayerController);
}

void SystemManager::addSystemMessage(std::unique_ptr<SystemMessageBase>& systemMessage)
{
	m_systemMessages.emplace_back(std::move(systemMessage));
}

void SystemManager::update()
{
	for (const auto& system : m_systems)
	{
		system->update();
	}

	handleSystemMessages();
}

void SystemManager::draw(sf::RenderWindow& window)
{
	const auto& systemDrawable = getSystem(SystemType::Drawable).get();
	static_cast<SystemDrawable*>(systemDrawable)->draw(window);
}

void SystemManager::addSystem(SystemType systemType)
{ 
	assert(!m_systems[static_cast<size_t>(systemType)].get());
	m_systems[static_cast<size_t>(systemType)] = m_systemFactory.getSystem(systemType);
}

void SystemManager::handleSystemMessages()
{
	if (m_systemMessages.empty())
	{
		return;
	}

	for (const auto& systemMessage : m_systemMessages)
	{
		(systemMessage->m_systemType == SystemType::Global ? sendGlobalSystemMessage(systemMessage) : sendSystemMessage(systemMessage));
	}

	m_systemMessages.clear();
}

void SystemManager::sendSystemMessage(const std::unique_ptr<SystemMessageBase>& systemMessage) const
{
	getSystem(systemMessage->m_systemType)->onSystemMessage(systemMessage);
}

void SystemManager::sendGlobalSystemMessage(const std::unique_ptr<SystemMessageBase>& systemMessage) const
{
	for (const auto& system : m_systems)
	{
		system->onSystemMessage(systemMessage);
	}
}

const std::unique_ptr<SystemBase>& SystemManager::getSystem(SystemType type) const
{
	return m_systems[static_cast<size_t>(type)];
}