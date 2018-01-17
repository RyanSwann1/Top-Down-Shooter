#include <Utilities\EntityInitializer.h>
#include <Entities\Entity.h>
#include <Components\ComponentPosition.h>
#include <Components\ComponentDrawable.h>
#include <Managers\EntityManager.h>

void EntityInitializer::initializeEntity(const sf::Vector2f& startingPosition, std::unique_ptr<Entity>& entity, EntityManager& entityManager)
{
	auto& componentPosition = entityManager.getEntityComponent<ComponentPosition>(entity, ComponentType::Position);
	auto& componentDrawable = entityManager.getEntityComponent<ComponentDrawable>(entity, ComponentType::Drawable);
	switch (entity->m_name)
	{
	case EntityName::Player :
	{
		componentPosition.m_position = startingPosition;
		componentDrawable.m_shape.setFillColor(sf::Color::Green);
		break;
	}
	case EntityName::Zombie :
	{
		componentPosition.m_position = startingPosition;
		componentDrawable.m_shape.setFillColor(sf::Color::Red);
		break;
	}
	}
}
