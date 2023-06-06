#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "RenderSystem.h"
#include "TextureSystem.h"
#include "SoundSystem.h"
#include "TextSystem.h"
#include <string>

enum ResourceType
{
	TEXTURE,
	SOUND,
	TEXT
};

class ResourceManager
{
private:
	RenderSystem		m_renderSystem;
	TextureSystem		m_textureSystem;
	SoundSystem			m_soundSystem;
	TextSystem			m_textSystem;

	void*				m_dataBuffer;

public:
	ResourceManager();

	bool init();
	void free();

	bool loadDatabase(const std::string& path);
	void aquire();

};

#endif // !RESOURCE_MANAGER_H