#pragma once

#include <Components\ComponentType.h>

class ComponentBase
{
public:
	ComponentBase(ComponentType type)
		: m_type(type)
	{

	}
	virtual ~ComponentBase() {}
	ComponentBase(const ComponentBase&) = delete;
	ComponentBase& operator=(const ComponentBase&) = delete;
	ComponentBase(ComponentBase&&) = delete;
	ComponentBase&& operator=(ComponentBase&&) = delete;


private:
	const ComponentType m_type;
};