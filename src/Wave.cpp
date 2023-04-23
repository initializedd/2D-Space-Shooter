#include "Wave.h"
#include "Globals.h"

Wave::Wave()
	: m_enemies{}
	, m_wave{}
{
	for (int i = 0; i < 3; ++i)
	{
		Enemy enemy{ i * 200, 0 };
		
		enemy.setColliders();
		
		m_enemies.push_back(enemy);
	}
}

Wave::~Wave()
{
	for (int i = 0; i < m_enemies.size(); ++i)
	{
		m_enemies.erase(m_enemies.begin() + i);
	}
}

std::vector<Enemy>& Wave::getEnemies()
{
	return m_enemies;
}