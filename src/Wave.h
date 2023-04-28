#ifndef WAVE_H
#define WAVE_H

#include "Enemy.h"
#include <sstream>
#include <vector>

class Wave
{
private:
	std::vector<Enemy>				m_enemies;
	int								m_wave;
	Texture							m_waveTexture;
	std::stringstream				m_waveText;

public:
	Wave();
	~Wave();

	void createWave();
	bool displayWaveNum();

	std::vector<Enemy>& getEnemies();
	Texture& getWaveTexture();
	int getWave();
};

#endif // !WAVE_H