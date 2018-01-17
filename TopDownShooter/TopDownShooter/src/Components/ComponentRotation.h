#pragma once

#include <Components\ComponentBase.h>

class ComponentRotation : public ComponentBase
{
public:
	ComponentRotation(ComponentType type)
		: ComponentBase(type)
	{}
	ComponentRotation(const ComponentRotation&) = delete;
	ComponentRotation& operator=(const ComponentRotation) = delete;
	ComponentRotation(ComponentRotation&&) = delete;
	ComponentRotation&& operator=(ComponentRotation&&) = delete;
};