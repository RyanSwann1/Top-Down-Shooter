#pragma once

#include <SFML\Graphics.hpp>
#include <Systems\SystemMessage.h>

class SystemMessagePosition : public SystemMessageBase
{
public:
	SystemMessagePosition(const sf::Vector2f& position, std::unique_ptr<Entity>& entity, SystemEvent systemEvent, SystemType systemType, SystemMessageType messageType)
		: SystemMessageBase(entity, systemEvent, systemType, messageType),
		m_position(position)
	{}

	const sf::Vector2f m_position;
};