#pragma once

#include <memory>
#include <Systems\SystemEvent.h>
#include <Systems\SystemType.h>
#include <Systems\SystemMessageType.h>

class Entity;
class SystemMessageBase
{
public:
	SystemMessageBase(std::unique_ptr<Entity>& entity, SystemEvent systemEvent, SystemType systemType, SystemMessageType messageType)
		: m_systemEvent(systemEvent),
		m_systemType(systemType),
		m_messageType(messageType),
		m_entity(entity)
	{}
	virtual ~SystemMessageBase() {}

	const SystemEvent m_systemEvent;
	const SystemType m_systemType;
	const SystemMessageType m_messageType;
	std::unique_ptr<Entity>& m_entity;
};