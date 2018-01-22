#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <assert.h>
#include <utility>
#include <memory>

template <class Resource>
class ResourceManager
{
public:
	ResourceManager()
		: m_resources(),
		m_filePaths()
	{}
	virtual ~ResourceManager() {}
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager&& operator=(ResourceManager&&) = delete;

	void addResource(std::string&& resourceName, const std::unique_ptr<Resource>& resource)
	{
		auto iter = m_resources.find(resourceName);
		assert(iter != m_resources.cend());
		m_resources.emplace(std::move(resourceName), resource);
	}

	const Resource& getResource(const std::string& name) const
	{
		auto iter = m_resources.find(name);
		assert(iter != m_resources.cend());
		return *iter->second.get();
	}

	bool hasResource(const std::string& name) const
	{
		auto iter = m_resources.find(name);
		return (iter != m_resources.cend() ? true : false);
	}

	void removeResource(const std::string& name)
	{
		auto iter = m_resources.find(name);
		assert(iter != m_resources.cend());
		m_resources.erase(iter);
	}

	void addFilePath(std::string&& name, std::string&& location)
	{
		assert(m_filePaths.find(name) == m_filePaths.cend());
		m_filePaths.emplace(std::move(name), std::move(location));
	}

protected:
	void removeAllResources()
	{
		m_resources.clear();
	}

private:
	std::unordered_map<std::string, std::unique_ptr<Resource>> m_resources;
	std::unordered_map<std::string, std::string> m_filePaths;
};