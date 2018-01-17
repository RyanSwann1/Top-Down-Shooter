#pragma once

#include <Components\ComponentBase.h>
#include <SFML\Graphics.hpp>

class ComponentDrawable : public ComponentBase
{
public:
	ComponentDrawable(ComponentType type)
		: ComponentBase(type),
		m_shape(sf::Vector2f(32, 32))
	{
		m_shape.setOrigin(sf::Vector2f(16, 16));
	}

	ComponentDrawable(const ComponentDrawable&) = delete;
	ComponentDrawable& operator=(const ComponentDrawable&) = delete;
	ComponentDrawable(ComponentDrawable&&) = delete;
	ComponentDrawable&& operator=(ComponentDrawable&&) = delete;

	sf::RectangleShape m_shape;
};