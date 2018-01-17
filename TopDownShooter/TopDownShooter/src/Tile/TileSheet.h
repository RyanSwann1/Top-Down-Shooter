#pragma once

#include <string>
#include <SFML\Graphics.hpp>

class TileSheet
{
public:
	TileSheet(std::string&& tileSheetName, int tileSize, int columns, int rows, int firstGID, int margin, int spacing);
	TileSheet(const TileSheet&) = delete;
	TileSheet& operator=(const TileSheet&) = delete;
	TileSheet(TileSheet&&) = delete;
	TileSheet&& operator=(TileSheet&&) = delete;

	sf::IntRect getTileLocation(int tileID) const;
	const sf::Texture& getTexture() const;
	void releaseTileSheet() const;

	const std::string m_name;
	const int m_tileSize;
	const int m_columns;
	const int m_rows;
	const int m_firstGID;
	const int m_margin;
	const int m_spacing;

private:
	sf::Texture m_tileSheet;
};