#pragma once

#include <memory>
#include <Components\ComponentBase.h>
#include <Entities\EntityName.h>
#include <Entities\EntityTag.h>
#include <array>

class Entity
{
public:
	Entity(EntityTag tag, EntityName name, int ID)
		: m_tag(tag),
		m_ID(ID),
		m_name(name),
		m_components()
	{}

	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;
	Entity(Entity&&) = delete;
	Entity&& operator=(Entity&&) = delete;

	const int m_ID;
	const EntityName m_name;
	const EntityTag m_tag;
	std::array<std::unique_ptr<ComponentBase>, static_cast<size_t>(ComponentType::Total)> m_components;
};