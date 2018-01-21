#pragma once

#include <States\StateBase.h>
#include <Managers\SystemManager.h>
#include <Managers\EntityManager.h>
#include <Managers\TileSheetManager.h>

class StateGame : public StateBase
{
public:
	StateGame(StateManager& stateManager, StateType type);
	StateGame(const StateGame&) = delete;
	StateGame& operator=(const StateGame&) = delete;
	StateGame(StateGame&&) = delete;
	StateGame&& operator=(StateGame&&) = delete;

	void update() override final;
	void draw(sf::RenderWindow& window) override final;

private:
	EntityManager m_entityManager;
	SystemManager m_systemManager;
	TileSheetManager m_tileSheetManager;
};