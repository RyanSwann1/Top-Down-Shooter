#include <Managers\EntityManager.h>
#include <Components\ComponentDrawable.h>
#include <Components\ComponentPosition.h>
#include <Components\ComponentMovable.h>
#include <Components\ComponentRotation.h>
#include <Locators\StringToEnumConverterLocator.h>
#include <Utilities\StringToEnumConverter.h>
#include <Utilities\EntityInitializer.h>
#include <Locators\EntityManagerLocator.h>
#include <algorithm>

//Component Factory
EntityManager::ComponentFactory::ComponentFactory()
{
	registerComponent<ComponentPosition>(ComponentType::Position);
	registerComponent<ComponentDrawable>(ComponentType::Drawable);
	registerComponent<ComponentMovable>(ComponentType::Movable);
	registerComponent<ComponentRotation>(ComponentType::Rotation);
}

std::unique_ptr<ComponentBase> EntityManager::ComponentFactory::getComponent(ComponentType type) const
{
	auto cIter = m_componentFactory.find(type);
	assert(cIter != m_componentFactory.cend());
	return cIter->second();
}

//Entity Factory
EntityManager::EntityFactory::EntityFactory(const ComponentFactory& componentFactory)
	: m_componentFactory(componentFactory),
	m_entityFactory()
{
	registerEntity("Player", { ComponentType::Drawable, ComponentType::Position, ComponentType::Movable, ComponentType::Rotation}, EntityTag::Player);
	registerEntity("Zombie", { ComponentType::Drawable, ComponentType::Position, ComponentType::Movable}, EntityTag::Enemy);
}

std::unique_ptr<Entity> EntityManager::EntityFactory::getEntity(const std::string& name, int& entityID)
{
	auto iter = m_entityFactory.find(name);
	assert(iter != m_entityFactory.cend());
	const EntityName entityName = StringToEnumConverterLocator::get().getEntityName(name);
	auto entity = std::make_unique<Entity>(iter->second.m_tag, entityName, entityID);
	++entityID;

	//Assign Components
	for (const auto componentType : iter->second.m_components)
	{
		entity->m_components[static_cast<size_t>(componentType)] = m_componentFactory.getComponent(componentType);
	}

	return entity;
}

void EntityManager::EntityFactory::registerEntity(const std::string& entityName, std::vector<ComponentType>&& entityComponents, EntityTag tag)
{
	assert(m_entityFactory.find(entityName) == m_entityFactory.cend());
	m_entityFactory.emplace(entityName, EntityInFactory(entityName, std::move(entityComponents), tag));
}

//Entity Manager
EntityManager::EntityManager()
	: m_componentFactory(),
	m_entityFactory(m_componentFactory),
	m_entities(),
	m_entityQueue(),
	m_removals(),
	m_entityID(0)
{
	EntityManagerLocator::provide(*this);
}

std::unique_ptr<Entity>& EntityManager::getEntityWithTag(EntityTag entityTag)
{
	auto iter = std::find_if(m_entities.begin(), m_entities.end(), [entityTag](const auto& entity) { return entity->m_tag == entityTag; });
	assert(iter != m_entities.cend());
	return *iter;
}

std::vector<std::unique_ptr<Entity>>& EntityManager::getEntities()
{
	return m_entities;
}

void EntityManager::addEntity(const sf::Vector2f & startingPosition, std::string && name)
{
	m_entityQueue.emplace_back(startingPosition, std::move(name));
}

void EntityManager::removeEntity(int entityID)
{
	auto iter = std::find_if(m_removals.cbegin(), m_removals.cend(), [entityID](const auto& removal) { return removal == entityID; });
	assert(iter != m_removals.cend());
	m_removals.erase(iter);
}

void EntityManager::update()
{
	handleEntityQueue();
	handleRemovals();
}

void EntityManager::handleEntityQueue()
{
	for (const auto& entityInQueue : m_entityQueue)
	{
		addEntityFromQueue(entityInQueue);
	}

	m_entityQueue.clear();
}

void EntityManager::handleRemovals()
{
	for (const auto entityIDToRemove : m_removals)
	{
		auto iter = std::find_if(m_entities.begin(), m_entities.end(), [entityIDToRemove](const auto& entity) { return entity->m_ID == entityIDToRemove; });
		assert(iter != m_entities.cend());
		m_entities.erase(iter);
	}

	m_removals.clear();
}

void EntityManager::addEntityFromQueue(const EntityInQueue & entityInQueue)
{
	auto entity = m_entityFactory.getEntity(entityInQueue.m_name, m_entityID);
	//Initialize Entity
	EntityInitializer::initializeEntity(entityInQueue.m_position, entity, *this);
	m_entities.emplace_back(std::move(entity));
}