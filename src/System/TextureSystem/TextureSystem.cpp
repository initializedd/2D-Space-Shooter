#include "TextureSystem.h"
#include "../../Resource/resourcedb_generated.h"
#include <SDL_image.h>
#include <cstdio>

TextureSystem::TextureSystem()
	: m_textures{}
	, m_textureIndexByName{}
	, m_sprites{}
	, m_spriteIndexByName{}
{
	init();
}

TextureSystem::~TextureSystem()
{
	m_textures.clear();
	m_sprites.clear();

	IMG_Quit();
}

bool TextureSystem::init()
{
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		printf("Failed to initialize IMG, Error: %s\n", IMG_GetError());
		return false;
	}

	return true;
}

bool TextureSystem::loadTexture(const std::string& name, const std::string& path)
{
	static std::size_t index = 0;

	if (m_textureIndexByName.contains(name))
		return false; // already loaded

	std::shared_ptr<Texture> texture = std::make_shared<Texture>();

	if (!texture->loadFromFile(path.c_str(), false))
		return false;

	m_textures.push_back(texture);

	// Add the textures name and index so we can search for it later
	m_textureIndexByName.insert({ name, index });
	++index;

	return true;
}

bool TextureSystem::loadSprite(const std::string& name, const std::string& path, int width, int height, int padding, int elements)
{
	static std::size_t index = 0;

	if (m_spriteIndexByName.contains(name))
		return false; // already loaded

	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>();

	if (!sprite->loadFromFile(path.c_str(), false))
		return false;

	sprite->setClipsFromSprite(width, height, padding, elements);

	m_sprites.push_back(sprite);

	// Add the sprites name and index so we can search for it later
	m_spriteIndexByName.insert({ name, index });
	++index;

	return true;
}

std::shared_ptr<Texture> TextureSystem::findTexture(const std::string& name)
{
	auto it = m_textureIndexByName.find(name);

	if (it == m_textureIndexByName.end())
	{
		printf("%s does not exist\n", name.c_str());
		return nullptr;
	}

	return m_textures[it->second];
}

std::shared_ptr<Sprite> TextureSystem::findSprite(const std::string& name)
{
	auto it = m_spriteIndexByName.find(name);

	if (it == m_spriteIndexByName.end())
	{
		printf("%s does not exist\n", name.c_str());
		return nullptr;
	}

	return m_sprites[it->second];
}

std::vector<std::shared_ptr<Texture>>& TextureSystem::getTextures()
{
	return m_textures;
}

std::vector<std::shared_ptr<Sprite>>& TextureSystem::getSprites()
{
	return m_sprites;
}