#pragma once

#include <Systems\SystemType.h>
#include <memory>

class EntityManager;
class SystemManager;
class Entity;
class SystemMessageBase;
class SystemBase
{
public:
	SystemBase(SystemManager& systemManager, SystemType type)
		: m_systemManager(systemManager),
		m_type(type)
	{}
	virtual ~SystemBase() {}
	SystemBase(const SystemBase&) = delete;
	SystemBase& operator=(const SystemBase&) = delete;
	SystemBase(SystemBase&&) = delete;
	SystemBase&& operator=(SystemBase&&) = delete;

	virtual void update() const {}
	virtual void onSystemMessage(const std::unique_ptr<SystemMessageBase>& systemMessage) const {}

	const SystemType m_type;

protected:
	SystemManager& m_systemManager;

	bool entityFitsRequirements(const std::unique_ptr<Entity>& entity, EntityManager& entityManager) const;
};