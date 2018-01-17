#pragma once

#include <States\StateType.h>
#include <SFML\Graphics.hpp>

class StateManager;
class StateBase
{
public:
	StateBase(StateManager& stateManager, StateType stateType)
		: m_type(stateType),
		m_stateManager(stateManager)
	{}
	virtual ~StateBase() {}
	StateBase(const StateBase&) = delete;
	StateBase& operator=(const StateBase&) = delete;
	StateBase(StateBase&&) = delete;
	StateBase&& operator=(StateBase&&) = delete;

	StateType getType() const { return m_type; }

	virtual void update() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

private:
	const StateType m_type;
	StateManager& m_stateManager;
};