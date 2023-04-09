#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>

class Sound
{
private:
	Mix_Music*		m_music;
	Mix_Chunk*		m_chunk;

public:
	Sound();
	~Sound();

	bool loadMusic(const char* path);
	bool playMusic(int loops);

	bool loadChunk(const char* path);
	bool playChunk(int channel, int loops);
};

#endif // !SOUND_H