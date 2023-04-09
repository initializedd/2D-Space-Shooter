#include "Sound.h"
#include <cstdio>

Sound::Sound()
	: m_music{}
	, m_chunk{}
{
}

Sound::~Sound()
{
	if (m_music)
	{
		Mix_FreeMusic(m_music);
		m_music = nullptr;
	}

	if (m_chunk)
	{
		Mix_FreeChunk(m_chunk);
		m_chunk = nullptr;
	}
}

bool Sound::loadMusic(const char* path)
{
	m_music = Mix_LoadMUS(path);
	if (!m_music)
	{
		printf("Failed to load %s into music, Error: %s\n", path, Mix_GetError());
		return false;
	}
}

bool Sound::playMusic(int loops)
{
	if (Mix_PlayMusic(m_music, loops) == -1)
	{
		printf("Failed to play music, Error: %s\n", Mix_GetError());
		return false;
	}

	return true;
}

bool Sound::loadChunk(const char* path)
{
	m_chunk = Mix_LoadWAV(path);
	if (!m_chunk)
	{
		printf("Failed to load %s into audio chunk, Error: %s\n", path, Mix_GetError());
		return false;
	}

	return true;
}

bool Sound::playChunk(int channel, int loops)
{
	if (Mix_PlayChannel(channel, m_chunk, loops) == -1)
	{
		printf("Failed to play audio chunk on channel %d, Error: %s\n", channel, Mix_GetError());
		return false;
	}

	return true;
}
