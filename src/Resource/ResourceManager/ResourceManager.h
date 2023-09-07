#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

//#include "Resource.h"
#include "../../System/RenderSystem/RenderSystem.h"
#include "../../System/TextureSystem/TextureSystem.h"
#include "../../System/SoundSystem/SoundSystem.h"
#include "../../System/TextSystem/TextSystem.h"
#include "../resourcedb_generated.h"
#include <flatbuffers/flatbuffers.h>
#include <string>

class ResourceManager
{
private:
	const ResourceDB::Root*						m_root;
												
	RenderSystem								m_renderSystem;
	TextureSystem								m_textureSystem;
	SoundSystem									m_soundSystem;
	TextSystem									m_textSystem;

	void*										m_dataBuffer;

	//std::vector<std::shared_ptr<Resource>>		m_resources;
	//std::unordered_map<std::string, uint32_t>	m_resourceNameByIndex;
	//std::size_t									m_index;

public:
	ResourceManager();
	~ResourceManager();
	
	bool loadDatabase(const std::string& path);

	RenderSystem& getRenderSystem();
	TextureSystem& getTextureSystem();
	SoundSystem& getSoundSystem();
	TextSystem& getTextSystem();

	//std::vector<std::shared_ptr<Resource>>& getResources();
};

#endif // !RESOURCE_MANAGER_H