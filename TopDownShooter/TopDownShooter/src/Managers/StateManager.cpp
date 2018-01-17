#include <Managers\StateManager.h>
#include <States\StateGame.h>
#include <Window.h>
#include <algorithm>

//StateFactory
StateManager::StateFactory::StateFactory(StateManager* stateManager)
{
	registerState<StateGame>(stateManager, StateType::Game);
}

std::unique_ptr<StateBase> StateManager::StateFactory::getState(StateType type) const
{
	auto iter = m_stateFactory.find(type);
	assert(iter != m_stateFactory.cend());
	return iter->second();
}

//StateManager
StateManager::StateManager()
	: m_stateFactory(this),
	m_states()
{}

StateType StateManager::getCurrentStateType() const
{
	assert(!m_states.empty());
	return m_states.front().get()->getType();
}

void StateManager::switchToState(StateType type)
{
	if (!m_states.empty())
	{
		assert(m_states.front().get()->getType() != type);
	}

	//Find existing state to switch to
	for (auto iter = m_states.begin(); iter != m_states.end(); ++iter)
	{
		if (iter->get()->getType() == type)
		{
			std::iter_swap(m_states.begin(), iter);
			return;
		}
	}

	//Create new state and switch to it
	m_states.push_front(m_stateFactory.getState(type));
}

void StateManager::update()
{
	if (m_states.empty())
	{
		return;
	}

	m_states.front().get()->update();
}

void StateManager::draw(sf::RenderWindow& window)
{
	for (const auto& state : m_states)
	{
		state->draw(window);
	}
}