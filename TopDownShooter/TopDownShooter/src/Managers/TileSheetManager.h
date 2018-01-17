#pragma once

#include <Managers\ResourceManager.h>
#include <Level\TileSheet.h>

class TileSheetManager : ResourceManager<TileSheet>
{
public:
	TileSheetManager(const TileSheetManager&) = delete;
	TileSheetManager& operator=(const TileSheetManager&) = delete;
	TileSheetManager(TileSheetManager&&) = delete;
	TileSheetManager&& operator=(TileSheetManager&&) = delete;



private:
	
};