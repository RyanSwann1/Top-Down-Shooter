#pragma once

#include <SFML\Graphics.hpp>
class Tile
{
public:
	Tile(const sf::Vector2i& position, int tileID);

	sf::Sprite m_sprite;
};