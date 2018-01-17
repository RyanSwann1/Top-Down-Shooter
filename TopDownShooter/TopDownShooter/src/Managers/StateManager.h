#pragma once

#include <States\StateBase.h>
#include <deque>
#include <memory>
#include <functional>
#include <unordered_map>
#include <assert.h>

class StateManager
{
	class StateFactory
	{
	public:
		StateFactory(StateManager* stateManager);
		StateFactory(const StateFactory&) = delete;
		StateFactory& operator=(const StateFactory&) = delete;
		StateFactory(StateFactory&&) = delete;
		StateFactory&& operator=(StateFactory&&) = delete;
		
		std::unique_ptr<StateBase> getState(StateType type) const;

	private:
		std::unordered_map<StateType, std::function<std::unique_ptr<StateBase>()>> m_stateFactory;

		template <class State>
		void registerState(StateManager* stateManager, StateType state)
		{
			assert(m_stateFactory.find(state) == m_stateFactory.cend());
			m_stateFactory.emplace(state, [state, stateManager]() -> std::unique_ptr<StateBase>
			{
				return std::make_unique<State>(*stateManager, state);
			});
		}
	};

public:
	StateManager();
	StateManager(const StateManager&) = delete;
	StateManager& operator=(const StateManager&) = delete;
	StateManager(StateManager&&) = delete;
	StateManager&& operator=(StateManager&&) = delete;

	StateType getCurrentStateType() const;

	void switchToState(StateType type);
	void update();
	void draw(sf::RenderWindow& window);
	
private:
	const StateFactory m_stateFactory;
	std::deque<std::unique_ptr<StateBase>> m_states;
};