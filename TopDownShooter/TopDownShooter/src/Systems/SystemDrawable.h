#pragma once

#include <Systems\SystemBase.h>
#include <SFML\Graphics.hpp>

class SystemDrawable : public SystemBase
{
public:
	SystemDrawable(SystemManager& systemManager, SystemType type);
	SystemDrawable(const SystemDrawable&) = delete;
	SystemDrawable& operator=(const SystemDrawable&) = delete;
	SystemDrawable(SystemDrawable&&) = delete;
	SystemDrawable&& operator=(SystemDrawable&&) = delete;

	void draw(sf::RenderWindow& window) const;

private:
	void drawEntity(std::unique_ptr<Entity>& entity, EntityManager& entityManager, sf::RenderWindow& window) const;
};