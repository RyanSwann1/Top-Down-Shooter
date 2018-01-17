#pragma once

#include <SFML\Graphics.hpp>
#include <Managers\ResourceManager.h>

class TextureManager : private ResourceManager<sf::Texture>
{
public:
	TextureManager() {}
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager&& operator=(TextureManager&&) = delete;

private:

};