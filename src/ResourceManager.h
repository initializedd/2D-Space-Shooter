#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "RenderSystem.h"
#include "TextureSystem.h"
#include "SoundSystem.h"
#include "TextSystem.h"
#include <flatbuffers/flatbuffers.h>
#include "resourcedb_generated.h"
#include <string>

class ResourceManager
{
private:
	const ResourceDB::Root*		m_root;

	RenderSystem				m_renderSystem;
	TextureSystem				m_textureSystem;
	SoundSystem					m_soundSystem;
	TextSystem					m_textSystem;

	void*						m_dataBuffer;

public:
	ResourceManager();
	~ResourceManager();
	
	bool loadDatabase(const std::string& path);

	RenderSystem& getRenderSystem();
	TextureSystem& getTextureSystem();
	SoundSystem& getSoundSystem();
	TextSystem& getTextSystem();
};

#endif // !RESOURCE_MANAGER_H