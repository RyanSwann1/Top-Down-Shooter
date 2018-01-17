#include "SystemBase.h"
#include <Managers\EntityManager.h>

bool SystemBase::entityFitsRequirements(const std::unique_ptr<Entity>& entity, EntityManager & entityManager) const
{
	return true;
}
