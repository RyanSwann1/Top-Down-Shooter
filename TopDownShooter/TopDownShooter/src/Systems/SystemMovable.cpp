#include <Systems\SystemMovable.h>
#include <Locators\EntityManagerLocator.h>
#include <Managers\EntityManager.h>
#include <Components\ComponentMovable.h>
#include <Components\ComponentPosition.h>
#include <Systems\SystemMessageBase.h>

SystemMovable::SystemMovable(SystemManager & systemManager, SystemType type)
	: SystemBase(systemManager, type)
{}

void SystemMovable::update() const
{
	auto& entityManager = EntityManagerLocator::get();
	for (auto& entity : entityManager.getEntities())
	{
		if (!SystemBase::entityFitsRequirements(entity, entityManager))
		{
			continue;
		}
	
		handleMovementDirection(entity, entityManager);
	}
}

void SystemMovable::onSystemMessage(const std::unique_ptr<SystemMessageBase>& systemMessage) const
{
	auto& entityManager = EntityManagerLocator::get();
	if (!SystemBase::entityFitsRequirements(systemMessage->m_entity, entityManager))
	{
		return;
	}

	handleSystemMessage(systemMessage, entityManager);
}

void SystemMovable::handleMovementDirection(std::unique_ptr<Entity>& entity, EntityManager & entityManager) const
{
	auto& componentMovable = entityManager.getEntityComponent<ComponentMovable>(entity, ComponentType::Movable);
	switch (componentMovable.m_direction)
	{
	case Direction::Right :
	{
		moveEntity(sf::Vector2f(componentMovable.m_speed.x, 0), componentMovable, entity, entityManager);
		break;
	}
	case Direction::Left :
	{
		moveEntity(sf::Vector2f(-componentMovable.m_speed.x, 0), componentMovable, entity, entityManager);
		break;
	}
	case Direction::Up :
	{
		moveEntity(sf::Vector2f(0, -componentMovable.m_speed.y), componentMovable, entity, entityManager);
		break;
	}
	case Direction::Down :
	{
		moveEntity(sf::Vector2f(0, componentMovable.m_speed.y), componentMovable, entity, entityManager);
		break;
	}
	}
}

void SystemMovable::moveEntity(const sf::Vector2f& movement, ComponentMovable& componentMovable, 
	std::unique_ptr<Entity>& entity, EntityManager & entityManager) const
{
	 auto& componentPosition = entityManager.getEntityComponent<ComponentPosition>(entity, ComponentType::Position);
	 //Assign a tickrate here/DeltaTime so movment is consistant on all computers
	 //Time taken each frame factored into consideration
	 componentPosition.m_position += movement;
	 componentMovable.m_direction = Direction::None;
}

void SystemMovable::handleSystemMessage(const std::unique_ptr<SystemMessageBase>& systemMessage, EntityManager& entityManager) const
{
	auto& componentMovable = entityManager.getEntityComponent<ComponentMovable>(systemMessage->m_entity, ComponentType::Movable);
	switch (systemMessage->m_systemEvent)
	{
	case SystemEvent::MoveLeft :
	{
		componentMovable.m_direction = Direction::Left;
		break;
	}
	case SystemEvent::MoveRight :
	{
		componentMovable.m_direction = Direction::Right;
		break;
	}
	case SystemEvent::MoveUp :
	{
		componentMovable.m_direction = Direction::Up;
		break;
	}
	case SystemEvent::MoveDown :
	{
		componentMovable.m_direction = Direction::Down;
		break;
	}
	}
}