#include "Tile.h"
#include <Locators\TileSheetManagerLocator.h>
#include <Managers\TileSheetManager.h>
#include <Window.h>

Tile::Tile(const sf::Vector2i & position, int tileID)
	: m_sprite()
{
	auto& tileSheet = TileSheetManagerLocator::get().getTileSheet(tileID);
	m_sprite.setTexture(tileSheet.getTexture());
	m_sprite.setPosition(sf::Vector2f(position.x * tileSheet.m_tileSize, position.y * tileSheet.m_tileSize));
}