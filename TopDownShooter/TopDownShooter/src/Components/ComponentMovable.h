#pragma once

#include <Components\ComponentBase.h>
#include <SFML\Graphics.hpp>
#include <Game\Direction.h>

class ComponentMovable : public ComponentBase
{
public:
	ComponentMovable(ComponentType type)
		: ComponentBase(type),
		m_speed(2, 2)
	{}
	
	ComponentMovable(const ComponentMovable&) = delete;
	ComponentMovable& operator=(const ComponentMovable&) = delete;
	ComponentMovable(ComponentMovable&&) = delete;
	ComponentMovable&& operator=(ComponentMovable&&) = delete;

	sf::Vector2f m_speed;
	Direction m_direction;
};