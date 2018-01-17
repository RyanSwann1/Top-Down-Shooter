#pragma once

#include <Entities\Entity.h>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_map>
#include <string>
#include <assert.h>
#include <utility>
#include <deque>
#include <SFML\Graphics.hpp>

class EntityManager
{
	class ComponentFactory
	{
	public:
		ComponentFactory();
		ComponentFactory(const ComponentFactory&) = delete;
		ComponentFactory& operator=(const ComponentFactory&) = delete;
		ComponentFactory(ComponentFactory&&) = delete;
		ComponentFactory&& operator=(ComponentFactory&&) = delete;

		std::unique_ptr<ComponentBase> getComponent(ComponentType type) const;
	
	private:
		std::unordered_map<ComponentType, std::function<std::unique_ptr<ComponentBase>()>> m_componentFactory;

		template <class Component>
		void registerComponent(ComponentType type)
		{
			assert(m_componentFactory.find(type) == m_componentFactory.cend());
			m_componentFactory.emplace(type, [type]() -> std::unique_ptr<ComponentBase>
			{
				return std::make_unique<Component>(type);
			});
		}
	};

	class EntityFactory
	{
		class EntityInFactory
		{
		public:
			EntityInFactory(const std::string& name, std::vector<ComponentType>&& components, EntityTag tag)
				: m_name(name),
				m_tag(tag),
				m_components(std::move(components))
			{}
		
			const std::string m_name;
			const EntityTag m_tag;
			const std::vector<ComponentType> m_components;
		};
	
	public:
		EntityFactory(const ComponentFactory& componentFactory);
		EntityFactory(const EntityFactory&) = delete;
		EntityFactory& operator=(const EntityFactory&) = delete;
		EntityFactory(EntityFactory&&) = delete;
		EntityFactory&& operator=(EntityFactory&&) = delete;

		std::unique_ptr<Entity> getEntity(const std::string& name, int& entityID);
		
	private:
		const ComponentFactory& m_componentFactory;
		std::unordered_map<std::string, EntityInFactory> m_entityFactory;

		void registerEntity(const std::string& entityName, std::vector<ComponentType>&& entityComponents, EntityTag entityTag);
	};

	class EntityInQueue
	{
	public:
		EntityInQueue(const sf::Vector2f& position, std::string&& name)
			: m_name(std::move(name)),
			m_position(position)
		{}

		const std::string m_name;
		const sf::Vector2f m_position;
	};

public:
	EntityManager();
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;
	EntityManager(EntityManager&&) = delete;
	EntityManager&& operator=(EntityManager&&) = delete;

	std::unique_ptr<Entity>& getEntityWithTag(EntityTag entityTag);
	std::vector<std::unique_ptr<Entity>>& getEntities();

	template <class Component>
	Component& getEntityComponent(std::unique_ptr<Entity>& entity, ComponentType componentType) const
	{
		assert(entity->m_components[static_cast<size_t>(componentType)].get());
		auto& component = entity->m_components[static_cast<size_t>(componentType)];
		return *static_cast<Component*>(component.get());
	}

	void addEntity(const sf::Vector2f& startingPosition, std::string&& name);
	void removeEntity(int entityID);
	void update();

private:
	const ComponentFactory m_componentFactory;
	EntityFactory m_entityFactory;
	std::vector<std::unique_ptr<Entity>> m_entities;
	std::deque<EntityInQueue> m_entityQueue;
	std::vector<int> m_removals;
	int m_entityID;

	void handleEntityQueue();
	void handleRemovals();
	void addEntityFromQueue(const EntityInQueue& entityInQueue);
};