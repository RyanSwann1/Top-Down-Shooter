#include <Managers\EventManager.h>
#include <locators\EventManagerLocator.h>
#include <Locators\GlobalMessengerLocator.h>
#include <Game\GlobalMessenger.h>
#include <Input\KeyCode.h>

EventManager::EventManager()
{
	EventManagerLocator::provide(*this);
}

bool EventManager::isKeyDown(KeyCode keyCode) const
{
	switch (keyCode)
	{
	case KeyCode::A :
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			return true;
		}
		break;
	}
	case KeyCode::D :
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			return true;
		}
		break;
	}
	case KeyCode::S :
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			return true;
		}
		break;
	}
	case KeyCode::W :
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			return true;
		}
		break;
	}
	}

	return false;
}

bool EventManager::isKeyReleased() const
{
	return true;
}

void EventManager::update(const sf::Event & sfmlEvent) const
{
	switch (sfmlEvent.type)
	{
	case sf::Event::Closed :
	{
		auto& globalMessenger = GlobalMessengerLocator::get();
		globalMessenger.activateMessage(GlobalMessage::CloseWindow);
		break;
	}
	}
}
