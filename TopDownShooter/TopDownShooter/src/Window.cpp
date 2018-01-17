#include <Window.h>
#include <Locators\GlobalMessengerLocator.h>
#include <Locators\WindowLocator.h>
#include <Game\GlobalMessenger.h>

Window::Window(const sf::Vector2u & size, std::string&& name)
	: m_window(sf::VideoMode(size.x, size.y), std::move(name), sf::Style::Default)
{
	auto& globalMessenger = GlobalMessengerLocator::get();
	globalMessenger.addMessage(GlobalMessage::CloseWindow, std::bind(&Window::closeWindow, this));
	WindowLocator::provide(*this);
}

Window::~Window()
{
	auto& globalMessenger = GlobalMessengerLocator::get();
	globalMessenger.removeMessage(GlobalMessage::CloseWindow);
}

bool Window::isOpen() const
{
	return m_window.isOpen();
}

sf::RenderWindow & Window::getWindow()
{
	return m_window;
}

void Window::clearWindow()
{
	m_window.clear(sf::Color::Black);
}

void Window::draw(sf::Sprite & spriteToRender)
{
	m_window.draw(spriteToRender);
}

void Window::display()
{
	m_window.display();
}

void Window::update()
{
	sf::Event sfmlEvent;
	while (m_window.pollEvent(sfmlEvent))
	{
		m_eventManager.update(sfmlEvent);
	}
}

void Window::closeWindow()
{
	m_window.close();
}