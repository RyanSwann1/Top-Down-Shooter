#include <Game\Game.h>

Game::Game()
	: m_textureManager(),
	m_globalMessenger(),
	m_stringToEnumConverter(),
	m_window(sf::Vector2u(900, 900), "SFML_WINDOW"),
	m_stateManager()
{
	m_stateManager.switchToState(StateType::Game);
}

bool Game::isRunning() const
{
	return m_window.isOpen();
}

void Game::update()
{
	m_window.update();
	m_stateManager.update();
}

void Game::lateUpdate()
{}

void Game::draw()
{
	m_window.clearWindow();
	m_stateManager.draw(m_window.getWindow());
	m_window.display();
}