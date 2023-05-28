#ifndef WAVE_H
#define WAVE_H

#include "Enemy.h"
#include "WraithEnemy.h"
#include "Pair.h"
#include <vector>
#include <array>
#include <sstream>

class Wave
{
private:
	std::array<Vector2<int>, 6>		m_enemyPositions;
	int								m_currentWave;
	int								m_currentHealth;
	int								m_numOfEnemies;
	int								m_maxNumOfEnemies;
	Texture							m_waveTexture;
	std::stringstream				m_waveText;

public:
	Wave();
	~Wave();

	void createWave();
	bool displayWaveNum();

	Texture& getWaveTexture();
	int getWave();
};

#endif // !WAVE_H