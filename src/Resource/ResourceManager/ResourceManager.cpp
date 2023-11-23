#include "ResourceManager.h"
#include <flatbuffers/idl.h>

ResourceManager::ResourceManager()
	: m_root{}
	, m_renderSystem{}
	, m_textureSystem{}
	, m_soundSystem{}
	, m_textSystem{}
	, m_dataBuffer{}
{
}

ResourceManager::~ResourceManager()
{
	SDL_free(m_dataBuffer);
}

bool ResourceManager::loadDatabase(const std::string& path)
{
	std::size_t size{};
	void* data = SDL_LoadFile(path.c_str(), &size);
	if (!data)
	{
		printf("Failed to load database: %s\n", path.c_str());
		return false;
	}

	const ResourceDB::Root* root = ResourceDB::GetRoot(data);
	flatbuffers::Verifier verifier(static_cast<uint8_t*>(data), size);
	if (!ResourceDB::VerifyRootBuffer(verifier))
	{
		printf("Failed to verify root buffer\n");
		return false;
	}

	m_root = root;

	for (const auto& texture : *m_root->textures())
		m_textureSystem.loadTexture(texture->name()->str(), texture->path()->str());

	for (const auto& sprite : *m_root->sprites())
		m_textureSystem.loadSprite(sprite->name()->str(), sprite->path()->str(), sprite->width(), sprite->height(), sprite->padding(), sprite->elements());

	for (const auto& sound : *m_root->sounds())
		m_soundSystem.loadSound(sound->name()->str(), sound->path()->str());

	for (const auto& font : *m_root->fonts())
		m_textSystem.loadFont(font->name()->str(), font->path()->str(), font->point_size());

	for (const auto& text : *m_root->texts())
		m_textSystem.loadText(text->name()->str(), text->text()->str());

	for (const auto& text_streams : *m_root->text_streams())
		m_textSystem.loadTextStream(text_streams->name()->str());

	return true;
}

RenderSystem& ResourceManager::getRenderSystem()
{
	return m_renderSystem;
}

TextureSystem& ResourceManager::getTextureSystem()
{
	return m_textureSystem;
}

SoundSystem& ResourceManager::getSoundSystem()
{
	return m_soundSystem;
}

TextSystem& ResourceManager::getTextSystem()
{
	return m_textSystem;
}

//std::vector<std::shared_ptr<Resource>>& ResourceManager::getResources()
//{
//	return m_resources;
//}
