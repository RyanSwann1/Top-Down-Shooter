#pragma once

#include <Systems\SystemBase.h>
#include <SFML\Graphics.hpp>

class ComponentMovable;
class EntityManager;
class Entity;
class SystemMovable : public SystemBase
{
public:
	SystemMovable(SystemManager& systemManager, SystemType type);
	SystemMovable(const SystemMovable&) = delete;
	SystemMovable& operator=(const SystemMovable&) = delete;
	SystemMovable(SystemMovable&&) = delete;
	SystemMovable&& operator=(SystemMovable&&) = delete;

	void update() const override final;
	void onSystemMessage(const std::unique_ptr<SystemMessageBase>& systemMessage) const override final;

private:
	void handleMovementDirection(std::unique_ptr<Entity>& entity, EntityManager& entityManager) const;
	void moveEntity(const sf::Vector2f& movement, ComponentMovable& componentMovable, std::unique_ptr<Entity>& entity, EntityManager& entityManager) const;
	void handleSystemMessage(const std::unique_ptr<SystemMessageBase>& systemMessage, EntityManager& entityManager) const;
};