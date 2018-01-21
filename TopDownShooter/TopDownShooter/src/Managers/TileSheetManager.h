#pragma once

#include <map>
#include <unordered_map>
#include <Tile\TileSheet.h>

class TileSheetManager
{
public:
	TileSheetManager();
	TileSheetManager(const TileSheetManager&) = delete;
	TileSheetManager& operator=(const TileSheetManager&) = delete;
	TileSheetManager(TileSheetManager&&) = delete;
	TileSheetManager&& operator=(TileSheetManager&&) = delete;

	const TileSheet& getTileSheet(const std::string& tileSheetName) const;
	void addTileSheet(const TileSheet& tileSheet);

private:
	std::unordered_map<std::string, TileSheet> m_tileSheets;

	bool hasTileSheet(const std::string& tileSheetName) const;
};