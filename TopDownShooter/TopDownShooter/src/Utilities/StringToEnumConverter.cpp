#include <Utilities\StringToEnumConverter.h>
#include <Locators\StringToEnumConverterLocator.h>
#include <assert.h>
#include <utility>

StringToEnumConverter::StringToEnumConverter()
{
	registerEntityName("Player", EntityName::Player);
	registerEntityName("Zombie", EntityName::Zombie);

	StringToEnumConverterLocator::provide(*this);
}

EntityName StringToEnumConverter::getEntityName(const std::string& name) const
{
	auto cIter = m_entityNames.find(name);
	assert(cIter != m_entityNames.cend());
	return cIter->second;
}

void StringToEnumConverter::registerEntityName(std::string&& entityName, EntityName name)
{
	assert(m_entityNames.find(entityName) == m_entityNames.cend());
	m_entityNames.emplace(std::move(entityName), name);
}