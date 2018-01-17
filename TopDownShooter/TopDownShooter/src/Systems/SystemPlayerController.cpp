#include <Systems\SystemPlayerController.h>
#include <Managers\EntityManager.h>
#include <Locators\EntityManagerLocator.h>
#include <Components\ComponentMovable.h>
#include <Components\ComponentDrawable.h>
#include <Managers\SystemManager.h>
#include <Locators\EventManagerLocator.h>
#include <Managers\EventManager.h>
#include <Locators\WindowLocator.h>
#include <Window.h>
#include <Input\KeyCode.h>

SystemPlayerController::SystemPlayerController(SystemManager& systemManager, SystemType type)
	: SystemBase(systemManager, type)
{}

void SystemPlayerController::update() const
{
	auto& entityManager = EntityManagerLocator::get();
	if (entityManager.getEntities().empty())
	{
		return;
	}

	auto& player = entityManager.getEntityWithTag(EntityTag::Player);
	handlePlayerMovement(player, entityManager);
	handlePlayerRotation(player, entityManager);
}

void SystemPlayerController::handlePlayerMovement(std::unique_ptr<Entity>& player, EntityManager & entityManager) const
{
	auto& eventManager = EventManagerLocator::get();
	auto& playerEntity = entityManager.getEntityWithTag(EntityTag::Player);
	if (eventManager.isKeyDown(KeyCode::A))
	{
		m_systemManager.addSystemMessage(std::make_unique<SystemMessageBase>(playerEntity, 
			SystemEvent::MoveLeft, SystemType::Movable, SystemMessageType::Base));
	}
	else if (eventManager.isKeyDown(KeyCode::D))
	{
		m_systemManager.addSystemMessage(std::make_unique<SystemMessageBase>(playerEntity, 
			SystemEvent::MoveRight, SystemType::Movable, SystemMessageType::Base));
	}
	else if (eventManager.isKeyDown(KeyCode::S))
	{
		m_systemManager.addSystemMessage(std::make_unique<SystemMessageBase>(playerEntity, 
			SystemEvent::MoveDown, SystemType::Movable, SystemMessageType::Base));
	}
	else if (eventManager.isKeyDown(KeyCode::W))
	{
		m_systemManager.addSystemMessage(std::make_unique<SystemMessageBase>(playerEntity, 
			SystemEvent::MoveUp, SystemType::Movable, SystemMessageType::Base));
	}
}

void SystemPlayerController::handlePlayerRotation(std::unique_ptr<Entity>& player, EntityManager & entityManager) const
{
	auto& componentDrawable = entityManager.getEntityComponent<ComponentDrawable>(player, ComponentType::Drawable);
	sf::Vector2f curPos = componentDrawable.m_shape.getPosition();
	auto& window = WindowLocator::get();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window.getWindow());

	// now we have both the sprite position and the cursor
	// position lets do the calculation so our sprite will
	// face the position of the mouse
	const float PI = 3.14159265f;

	const float dx = curPos.x - mousePosition.x;
	const float dy = curPos.y - mousePosition.y;

	const float rotation = (atan2(dy, dx)) * 180 / PI;

	componentDrawable.m_shape.setRotation(rotation + 180);
}