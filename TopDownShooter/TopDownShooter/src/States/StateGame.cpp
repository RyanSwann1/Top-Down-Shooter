#include <States\StateGame.h>
#include <iostream>

StateGame::StateGame(StateManager& stateManager, StateType type)
	: StateBase(stateManager, type),
	m_systemManager(),
	m_entityManager()
{
	std::cout << "Entered State\n";
	m_entityManager.addEntity(sf::Vector2f(128, 128), "Player");
	m_entityManager.addEntity(sf::Vector2f(175, 175), "Zombie");
}

void StateGame::update()
{
	m_systemManager.update();
	m_entityManager.update();
}

void StateGame::draw(sf::RenderWindow & window)
{
	m_systemManager.draw(window);
}