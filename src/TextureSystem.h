#ifndef TEXTURE_SYSTEM_H
#define TEXTURE_SYSTEM_H

#include "Texture.h"
#include "Sprite.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

class TextureSystem
{
private:
	std::vector<std::shared_ptr<Texture>>			m_textures;
	std::unordered_map<std::string, uint32_t>		m_textureIndexByName;

	std::vector<std::shared_ptr<Sprite>>			m_sprites;
	std::unordered_map<std::string, uint32_t>		m_spriteIndexByName;
public:
	TextureSystem();
	~TextureSystem();

	bool init();

	bool loadTexture(const std::string& name, const std::string& path);
	std::shared_ptr<Texture> findTexture(const std::string& name);

	bool loadSprite(const std::string& name, const std::string& path, int width, int height, int padding, int elements);
	std::shared_ptr<Sprite> findSprite(const std::string& name);

	std::vector<std::shared_ptr<Texture>>& getTextures();
	std::vector<std::shared_ptr<Sprite>>& getSprites();
};

#endif // !TEXTURE_SYSTEM_H