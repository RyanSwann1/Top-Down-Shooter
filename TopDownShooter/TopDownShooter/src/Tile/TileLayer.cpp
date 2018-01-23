#include <Tile\TileLayer.h>
#include <assert.h>

TileLayer::TileLayer(std::vector<std::vector<int>>&& tileMap, const sf::Vector2i & levelSize)
{
	for (int row = 0; row < levelSize.y; ++row)
	{
		for (int col = 0; col < levelSize.x; ++col)
		{
			const int tileID = tileMap[row][col];
			if (tileID >= 0)
			{
				m_tileLayer.emplace_back(sf::Vector2i(col, row), tileID);
			}
		}
	}

	assert(!m_tileLayer.empty());
}

void TileLayer::draw(sf::RenderWindow & window) const
{
	for (const auto& tile : m_tileLayer)
	{
		window.draw(tile.m_sprite);
	}
}