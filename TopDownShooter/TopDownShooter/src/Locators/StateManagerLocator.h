#pragma once

#include <assert.h>

class StateManager;
class StateManagerLocator
{
public:
	static void provide(StateManager& stateManager)
	{
		m_stateManager = &stateManager;
	}

	static StateManager& get()
	{
		assert(m_stateManager);
		return *m_stateManager;
	}

private:
	static StateManager* m_stateManager;
};