#pragma once

#include <Window.h>
#include <Managers\StateManager.h>
#include <Utilities\StringToEnumConverter.h>
#include <Game\GlobalMessenger.h>

class Game
{
public:
	Game();
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game&& operator=(Game&&) = delete;

	bool isRunning() const;
	void update();
	void lateUpdate();
	void draw();
	
private:
	GlobalMessenger m_globalMessenger;
	StringToEnumConverter m_stringToEnumConverter;
	Window m_window;
	StateManager m_stateManager;
};