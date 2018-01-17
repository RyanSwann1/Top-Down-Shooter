#pragma once

#include <SFML\Graphics.hpp>
#include <Managers\EventManager.h>

class Window
{
public:
	Window(const sf::Vector2u& size, std::string&& name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(Window&) = delete;
	Window(Window&&) = delete;
	Window&& operator=(Window&&) = delete;

	bool isOpen() const;
	sf::RenderWindow& getWindow();

	void clearWindow();
	void draw(sf::Sprite& spriteToRender);
	void display();
	void update();
	
private:
	const EventManager m_eventManager;
	sf::RenderWindow m_window;

	void closeWindow();
};