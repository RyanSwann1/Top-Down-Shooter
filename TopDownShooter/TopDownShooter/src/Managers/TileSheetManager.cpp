#include <Managers\TileSheetManager.h>
#include <Locators\TileSheetManagerLocator.h>

TileSheetManager::TileSheetManager()
{
	TileSheetManagerLocator::provide(*this);
}

const TileSheet & TileSheetManager::getTileSheet(const std::string & tileSheetName) const
{
	auto cIter = m_tileSheets.find(tileSheetName);
	assert(cIter != m_tileSheets.cend());
	return cIter->second;
}

void TileSheetManager::addTileSheet(const TileSheet& tileSheet)
{
	assert(hasTileSheet(tileSheet.m_name));
	//std::unordered_map<std::string, TileSheet> m_tileSheets;
	m_tileSheets.emplace(tileSheet.m_name, tileSheet);
}

bool TileSheetManager::hasTileSheet(const std::string & tileSheetName) const
{
	auto cIter = m_tileSheets.find(tileSheetName);
	return (cIter != m_tileSheets.cend() ? true : false);
}