#pragma once

#include <SFML\Graphics.hpp>

enum class KeyCode;
class EventManager
{
public:
	EventManager();
	EventManager(const EventManager&) = delete;
	EventManager& operator=(const EventManager&) = delete;
	EventManager(EventManager&&) = delete;
	EventManager&& operator=(EventManager&&) = delete;

	bool isKeyDown(KeyCode keyCode) const;
	bool isKeyReleased() const;

	void update(const sf::Event& sfmlEvent) const;
};