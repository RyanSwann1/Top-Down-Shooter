#include <Systems\SystemDrawable.h>
#include <Components\ComponentDrawable.h>
#include <Components\ComponentPosition.h>
#include <Locators\EntityManagerLocator.h>
#include <Managers\EntityManager.h>
#include <Locators\WindowLocator.h>
#include <Window.h>

SystemDrawable::SystemDrawable(SystemManager & systemManager, SystemType type)
	: SystemBase(systemManager, type)
{}

void SystemDrawable::draw(sf::RenderWindow & window) const
{
	auto& entityManager = EntityManagerLocator::get();
	for (auto& entity : entityManager.getEntities())
	{
		if (!SystemBase::entityFitsRequirements(entity, entityManager))
		{
			continue;
		}

		drawEntity(entity, entityManager, window);
	}
}

void SystemDrawable::drawEntity(std::unique_ptr<Entity>& entity, EntityManager & entityManager, sf::RenderWindow& window) const
{
	auto& componentDrawable = entityManager.getEntityComponent<ComponentDrawable>(entity, ComponentType::Drawable);
	const auto& componentPosition = entityManager.getEntityComponent<ComponentPosition>(entity, ComponentType::Position);
	componentDrawable.m_shape.setPosition(componentPosition.m_position);
	

	sf::Vector2f curPos = componentDrawable.m_shape.getPosition();
	sf::Vector2i position = sf::Mouse::getPosition(window);

	// now we have both the sprite position and the cursor
	// position lets do the calculation so our sprite will
	// face the position of the mouse
	const float PI = 3.14159265;

	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;

	float rotation = (atan2(dy, dx)) * 180 / PI;

	componentDrawable.m_shape.setRotation(rotation + 180);
	window.draw(componentDrawable.m_shape);
}