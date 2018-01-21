#include <Managers\LevelManager.h>
#include <Managers\EntityManager.h>
#include <Tile\TileLayer.h>
#define TIXML_USE_STL
#include <Utilities\tinyxml.h>
#include <Utilities\Base64.h>
#include <Locators\EntityManagerLocator.h>
#include <Locators\TileSheetManagerLocator.h>
#include <Managers\TileSheetManager.h>

//Tile
LevelManager::Tile::Tile(const sf::Vector2f & position)
	: m_tile()
{
	m_tile.setPosition(position);
}

LevelManager::Tile::~Tile()
{

}

void LevelManager::Tile::draw(sf::RenderWindow & window) const
{
	window.draw(m_tile);
}

//Level
LevelManager::Level::Level(std::string&& name, std::vector<TileLayer>&& tileLayers)
	: m_name(std::move(name)),
	m_tileLayers(std::move(tileLayers))
{
}

const std::string & LevelManager::Level::getName() const
{
	return m_name;
}


class LevelDetails
{
public:
	LevelDetails(const sf::Vector2i& size, int tileSize)
		: m_levelSize(size),
		m_tileSize(tileSize)
	{}

	const sf::Vector2i m_levelSize;
	const int m_tileSize;
};

//Level Parser
std::vector<TileLayer> parseTileLayers(const TiXmlElement& rootElement, const sf::Vector2i& levelSize);
std::vector<sf::Vector2i> parseCollisionLayer(const TiXmlElement& rootElement, int tileSize);
LevelDetails parseLevelDetails(const TiXmlElement& rootElement);
std::vector<std::vector<int>> decodeTileLayer(const TiXmlElement & tileLayerElement, const sf::Vector2i& levelSize);
void parseTileSheets(const TiXmlElement& rootElement);
void parseEntities(const TiXmlElement& rootElement, EntityManager& entityManager, int tileSize);

std::vector<TileLayer> parseTileLayers(const TiXmlElement & rootElement, const sf::Vector2i & levelSize)
{
	std::vector<TileLayer> tileLayers;
	for (const auto* tileLayerElement = rootElement.FirstChildElement(); tileLayerElement != nullptr; tileLayerElement = tileLayerElement->NextSiblingElement())
	{
		if (tileLayerElement->Value() != std::string("layer"))
		{
			continue;
		}

		auto tileMap = decodeTileLayer(*tileLayerElement, levelSize);
		tileLayers.emplace_back(std::move(tileMap), levelSize);
	}

	assert(!tileLayers.empty());
	return tileLayers;
}

std::vector<sf::Vector2i> parseCollisionLayer(const TiXmlElement & rootElement, int tileSize)
{
	return std::vector<sf::Vector2i>();
}

LevelDetails parseLevelDetails(const TiXmlElement & rootElement)
{
	sf::Vector2i levelSize;
	int tileSize = 0;
	rootElement.Attribute("width", &levelSize.x);
	rootElement.Attribute("height", &levelSize.y);
	rootElement.Attribute("tilewidth", &tileSize);
	return LevelDetails(levelSize, tileSize);
}

std::vector<std::vector<int>> decodeTileLayer(const TiXmlElement & tileLayerElement, const sf::Vector2i & levelSize)
{
	std::vector<std::vector<int>> tileData;
	tileData.reserve(levelSize.y);

	std::string decodedIDs; //Base64 decoded information
	const TiXmlElement* dataNode = nullptr; //Store our node once we find it
	for (const TiXmlElement* e = tileLayerElement.FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		if (e->Value() == std::string("data"))
		{
			dataNode = e;
		}
	}
	assert(dataNode);

	Base64 base64;
	const TiXmlText* text = dataNode->FirstChild()->ToText();
	const std::string t = text->Value();
	decodedIDs = base64.base64_decode(t);

	const std::vector<int> layerColumns(levelSize.x);
	for (int i = 0; i < levelSize.y; ++i)
	{
		tileData.push_back(layerColumns);
	}

	for (int rows = 0; rows < levelSize.y; ++rows)
	{
		for (int cols = 0; cols < levelSize.x; ++cols)
		{
			tileData[rows][cols] = *((int*)decodedIDs.data() + rows * levelSize.x + cols) - 1;
		}
	}

	return tileData;
}

void parseTileSheets(const TiXmlElement & rootElement)
{
	for (const auto* tileSheetElement = rootElement.FirstChildElement();
		tileSheetElement != nullptr; tileSheetElement = tileSheetElement->NextSiblingElement())
	{
		if (tileSheetElement->Value() != std::string("tileset"))
		{
			continue;
		}

		std::string tileSheetName = tileSheetElement->Attribute("name");
		sf::Vector2i tileSetSize;
		int spacing = 0, margin = 0, tileSize = 0, firstGID = 0;
		tileSheetElement->FirstChildElement()->Attribute("width", &tileSetSize.x);
		tileSheetElement->FirstChildElement()->Attribute("height", &tileSetSize.y);
		tileSheetElement->Attribute("tilewidth", &tileSize);
		tileSheetElement->Attribute("spacing", &spacing);
		tileSheetElement->Attribute("firstgid", &firstGID);
		tileSheetElement->Attribute("margin", &margin);
		const int columns = tileSetSize.x / (tileSize + spacing);
		const int rows = tileSetSize.y / (tileSize + spacing);

		auto& tileSheetManager = TileSheetManagerLocator::get();
		tileSheetManager.addTileSheet(TileSheet(std::move(tileSheetName), tileSize, columns, rows, firstGID, margin, spacing));
	}
}

void parseEntities(const TiXmlElement & rootElement, EntityManager & entityManager, int tileSize)
{
	for (const auto* entityElementRoot = rootElement.FirstChildElement(); entityElementRoot != nullptr; entityElementRoot = entityElementRoot->NextSiblingElement())
	{
		if (entityElementRoot->Value() != std::string("objectgroup"))
		{
			continue;
		}

		if (entityElementRoot->Attribute("name") != std::string("Entity Layer"))
		{
			continue;
		}

		for (const auto* entityElement = entityElementRoot->FirstChildElement(); entityElement != nullptr; entityElement = entityElement->NextSiblingElement())
		{
			int xPosition = 0, yPosition = 0;
			entityElement->Attribute("x", &xPosition);
			entityElement->Attribute("y", &yPosition);
			std::string entityName = entityElement->Attribute("name");

			yPosition -= tileSize;
			entityManager.addEntity(sf::Vector2f(xPosition, yPosition), std::move(entityName));
		}
	}
}

LevelManager::LevelManager()
	: m_levels(),
	m_levelDirectories(getLevelDirectories())
{

}

void LevelManager::addLevel(const std::string & levelName)
{
	
}

void LevelManager::removeLevel(const std::string & levelName)
{
	auto iter = std::find_if(m_levels.begin(), m_levels.end(), [&levelName](const auto& level) { return level->getName() == levelName; });
	assert(iter != m_levels.cend());
	m_levels.erase(iter);
}

std::unique_ptr<LevelManager::Level> LevelManager::parseLevel(const std::string & fileDirectory, const std::string& levelName) const
{
	TiXmlDocument mapFile;
	const bool mapLoaded = mapFile.LoadFile(fileDirectory);
	assert(mapLoaded);

	const auto& rootElement = mapFile.RootElement();
	const LevelDetails levelDetails = parseLevelDetails(*rootElement);
	parseTileSheets(*rootElement);
	parseEntities(*rootElement, EntityManagerLocator::get(), levelDetails.m_tileSize);

	return std::make_unique<Level>(std::move(parseTileLayers(*rootElement, levelDetails.m_levelSize)),
		levelName, levelDetails.m_levelSize, levelDetails.m_tileSize);
}

std::unordered_map<std::string, std::string> LevelManager::getLevelDirectories() const
{
	std::unordered_map<std::string, std::string> levelDirectories;
	
	return levelDirectories;
}
