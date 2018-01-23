#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include <Tile\Tile.h>

class TileLayer
{
public:
	TileLayer(std::vector<std::vector<int>>&& tileMap, const sf::Vector2i& levelSize);

	void draw(sf::RenderWindow& window) const;

private:
	std::vector<Tile> m_tileLayer;
};