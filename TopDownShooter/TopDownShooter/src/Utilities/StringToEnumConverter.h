#pragma once

#include <Entities\EntityName.h>
#include <string>
#include <unordered_map>

class StringToEnumConverter
{
public:
	StringToEnumConverter();
	StringToEnumConverter(const StringToEnumConverter&) = delete;
	StringToEnumConverter& operator=(StringToEnumConverter&) = delete;
	StringToEnumConverter(StringToEnumConverter&&) = delete;
	StringToEnumConverter&& operator=(StringToEnumConverter&&) = delete;

	EntityName getEntityName(const std::string& name) const;
	
private:
	std::unordered_map<std::string, EntityName> m_entityNames;

	void registerEntityName(std::string&& entityName, EntityName name);
};