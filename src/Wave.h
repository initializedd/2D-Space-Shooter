#ifndef WAVE_H
#define WAVE_H

#include "Enemy.h"
#include <vector>

class Wave
{
private:
	std::vector<Enemy>		m_enemies;
	int						m_wave;

public:
	Wave();
	~Wave();

	std::vector<Enemy>& getEnemies();
};

#endif // !WAVE_H