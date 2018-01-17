#pragma once

#include <Systems\SystemBase.h>
#include <memory>

class Entity;
class EntityManager;
class SystemPlayerController : public SystemBase
{
public:
	SystemPlayerController(SystemManager& systemManager, SystemType type);
	SystemPlayerController(const SystemPlayerController&) = delete;
	SystemPlayerController& operator=(const SystemPlayerController&) = delete;
	SystemPlayerController(SystemPlayerController&&) = delete;
	SystemPlayerController&& operator=(SystemPlayerController&&) = delete;

	void update() const override final;

private:
	void handlePlayerMovement(std::unique_ptr<Entity>& player, EntityManager& entityManager) const;
	void handlePlayerRotation(std::unique_ptr<Entity>& player, EntityManager& entityManager) const;
};