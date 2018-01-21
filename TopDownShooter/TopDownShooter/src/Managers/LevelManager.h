#pragma once

#include <Tile\TileLayer.h>
#include <SFML\Graphics.hpp>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <unordered_map>

class LevelManager
{
	class Tile
	{
	public:
		Tile(const sf::Vector2f& position);
		~Tile();
		Tile(const Tile&) = delete;
		Tile& operator=(const Tile&) = delete;
		Tile(Tile&&) = delete;
		Tile&& operator=(Tile&&) = delete;

		void draw(sf::RenderWindow& window) const;

	private:
		sf::Sprite m_tile;
	};

	class Level
	{
	public:
		Level(std::string&& name, std::vector<TileLayer>&& tileLayers);

		const std::string& getName() const;


	private:
		const std::string m_name;
		const std::vector<TileLayer> m_tileLayers;
	};

public:
	LevelManager();
	LevelManager(const LevelManager&) = delete;
	LevelManager& operator=(const LevelManager&) = delete;
	LevelManager(LevelManager&&) = delete;
	LevelManager&& operator=(LevelManager&&) = delete;

	void addLevel(const std::string& levelName);
	void removeLevel(const std::string& levelName);

private:
	const std::unordered_map<std::string, std::string> m_levelDirectories;
	std::vector<std::unique_ptr<Level>> m_levels;
	
	std::unique_ptr<Level> parseLevel(const std::string& fileDirectory, const std::string& levelName) const;
	std::unordered_map<std::string, std::string> getLevelDirectories() const;
};