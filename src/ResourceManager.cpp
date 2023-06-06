#include "ResourceManager.h"

ResourceManager::ResourceManager()
	: m_renderSystem{}
	, m_textureSystem{}
	, m_soundSystem{}
	, m_textSystem{}
	, m_dataBuffer{}
{
}

bool ResourceManager::init()
{
	if (!m_renderSystem.init())
		return false;

	if (!m_textureSystem.init())
		return false;

	if (!m_soundSystem.init())
		return false;

	if (m_textSystem.init())
		return false;

	return true;
}

void ResourceManager::free()
{
	SDL_free(m_dataBuffer);

	m_textSystem.free();
	m_soundSystem.free();
	m_textureSystem.free();
	m_renderSystem.free();
}

bool ResourceManager::loadDatabase(const std::string& path)
{
	size_t size{};
	void* data = SDL_LoadFile(path.c_str(), &size);
	if (!data)
	{
		printf("Failed to load database: %s\n", path.c_str());
		return false;
	}

	return true;
}

void ResourceManager::aquire()
{

}