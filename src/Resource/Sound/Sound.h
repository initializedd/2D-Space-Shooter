#ifndef SOUND_H
#define SOUND_H

#include <SDL_mixer.h>
#include <string>

class Sound
{
private:
	Mix_Music*		m_music;
	Mix_Chunk*		m_chunk;

public:
	Sound();
	~Sound();

	bool loadMusic(const std::string& path);
	bool playMusic(int loops);

	bool loadChunk(const std::string& path);
	bool playChunk(int channel, int loops, int volume);
};

#endif // !SOUND_H