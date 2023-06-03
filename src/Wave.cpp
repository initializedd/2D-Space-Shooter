#include "Wave.h"
#include "Globals.h"

Wave::Wave()
	: m_currentWave{}
	, m_currentHealth{}
	, m_numOfEnemies{}
	, m_maxNumOfEnemies{}
	, m_waveTexture{}
	, m_waveText{}
{
	m_enemyPositions = { Vector2<int>(0, 0), Vector2<int>(160, 0), Vector2<int>(320, 0),
						 Vector2<int>(0, 180), Vector2<int>(160, 180), Vector2<int>(320, 180) };
}

Wave::~Wave()
{
	for (int i = NUM_OF_PLAYERS; i < gEnts.size(); ++i)
	{
		delete gEnts[i];
		gEnts.erase(gEnts.begin() + i);
	}
}

void Wave::createWave()
{
	if (gEnts.size() <= NUM_OF_PLAYERS)
	{
		++m_currentWave;

		if (m_currentWave <= 1)
			m_numOfEnemies = 2;

		if (m_currentWave >= 5)
			m_numOfEnemies = 6;

		for (int i = 0; i < m_numOfEnemies; ++i)
		{
			Enemy* enemy = new Enemy(m_enemyPositions[i].x + 80, m_enemyPositions[i].y + 50);

			enemy->getShip().setTexture(gShipsSprite);
			enemy->getShip().createShip(gShipsSprite->getIndex());

			enemy->setColliders();

			gEnts.push_back(enemy);

			WraithEnemy* wraithEnemy = new WraithEnemy(m_enemyPositions[i].x, m_enemyPositions[i].y);

			wraithEnemy->getShip().setTexture(gShipsSprite);
			wraithEnemy->getShip().createShip(gShipsSprite->getIndex());

			wraithEnemy->setColliders();

			gEnts.push_back(wraithEnemy);
		}
	}
}

bool Wave::displayWaveNum()
{
	m_waveText.str("Wave: " + std::to_string((m_currentWave)));

	if (!m_waveTexture.loadFromRenderedText(m_waveText.str().c_str(), gFuturaFont, SDL_Color(0x00, 0xFF, 0x00, 0xFF)))
		return false;

	return true;
}

Texture& Wave::getWaveTexture()
{
	return m_waveTexture;
}

int Wave::getWave()
{
	return m_currentWave;
}