#include "SoundSystem.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <cstdio>

SoundSystem::SoundSystem()
	: m_indexByName{}
	, m_sounds{}
{
	init();
}

SoundSystem::~SoundSystem()
{
	m_sounds.clear();

	Mix_Quit();
}

bool SoundSystem::init()
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("Failed to initialize SDL_INIT_AUDIO, Error: %s\n", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("Failed to initialize Mixer, Error: %s\n", Mix_GetError());
		return false;
	}

	Mix_AllocateChannels(20);

	return true;
}

bool SoundSystem::loadSound(const std::string& name, const std::string& path)
{
	static std::size_t index = 0;

	if (m_indexByName.contains(name))
		return false; // already loaded

	std::shared_ptr<Sound> sound = std::make_shared<Sound>();

	if (!sound->loadChunk(path))
		return false;

	m_sounds.push_back(sound);

	// Add the sounds name and index so we can search for it later
	m_indexByName.insert({ name, index });
	++index;

	return true;
}

std::shared_ptr<Sound> SoundSystem::findSound(const std::string& name)
{
	auto it = m_indexByName.find(name);

	if (it == m_indexByName.end())
	{
		printf("%s does not exist\n", name.c_str());
		return nullptr;
	}

	return m_sounds[it->second];
}

std::vector<std::shared_ptr<Sound>>& SoundSystem::getSounds()
{
	return m_sounds;
}