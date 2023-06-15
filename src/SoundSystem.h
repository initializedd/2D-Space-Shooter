#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include "Sound.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

class SoundSystem
{
private:
	std::unordered_map<std::string, uint32_t>		m_indexByName;
	std::vector<std::shared_ptr<Sound>>				m_sounds;

public:
	SoundSystem();
	~SoundSystem();

	bool init();

	bool loadSound(const std::string& name, const std::string& path);
	std::shared_ptr<Sound> findSound(const std::string& name);

	std::vector<std::shared_ptr<Sound>>& getSounds();
};

#endif // !SOUND_SYSTEM_H