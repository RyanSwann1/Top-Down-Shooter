#pragma once

#include <vector>
#include <memory>
#include <Systems\SystemBase.h>
#include <SFML\Graphics.hpp>
#include <array>
#include <unordered_map>
#include <functional>
#include <assert.h>
#include <deque>
#include <Systems\SystemMessageBase.h>

class Window;
class SystemManager
{
	class SystemFactory
	{
	public:
		SystemFactory(SystemManager* systemManager);
		SystemFactory(const SystemFactory&) = delete;
		SystemFactory& operator=(const SystemFactory&) = delete;
		SystemFactory(SystemFactory&&) = delete;
		SystemFactory&& operator=(SystemFactory&&) = delete;

		std::unique_ptr<SystemBase> getSystem(SystemType type) const;

	private:
		std::unordered_map<SystemType, std::function<std::unique_ptr<SystemBase>()>> m_systemFactory;

		template <class System>
		void registerSystem(SystemManager* systemManager, SystemType type)
		{
			assert(m_systemFactory.find(type) == m_systemFactory.cend());
			m_systemFactory.emplace(type, [systemManager, type]() -> std::unique_ptr<SystemBase>
			{
				return std::make_unique<System>(*systemManager, type);
			});
		}
	};

public:
	SystemManager();
	SystemManager(const SystemManager&) = delete;
	SystemManager& operator=(const SystemManager&) = delete;
	SystemManager(SystemManager&&) = delete;
	SystemManager&& operator=(SystemManager&&) = delete;

	void addSystemMessage(std::unique_ptr<SystemMessageBase>& systemMessage);

	void update();
	void draw(sf::RenderWindow& window);

private:
	const SystemFactory m_systemFactory;
	std::deque<std::unique_ptr<SystemMessageBase>> m_systemMessages;
	std::array<std::unique_ptr<SystemBase>, static_cast<size_t>(SystemType::Total)> m_systems;

	void addSystem(SystemType systemType);
	void handleSystemMessages();
	void sendSystemMessage(const std::unique_ptr<SystemMessageBase>& systemMessage) const;
	void sendGlobalSystemMessage(const std::unique_ptr<SystemMessageBase>& systemMessage) const;
	const std::unique_ptr<SystemBase>& getSystem(SystemType type) const;
};