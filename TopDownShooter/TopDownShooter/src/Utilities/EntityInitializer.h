#pragma once

#include <SFML\Graphics.hpp>
#include <memory>

class EntityManager;
class Entity;
namespace EntityInitializer
{
	void initializeEntity(const sf::Vector2f& startingPosition, std::unique_ptr<Entity>& entity, EntityManager& entityManager);
}