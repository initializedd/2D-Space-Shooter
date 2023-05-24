#include "Wave.h"
#include "Globals.h"

Wave::Wave()
	: m_enemies{}
	, m_wave{}
	, m_waveTexture{}
	, m_waveText{}
{
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
		for (int i = 0; i < 3; ++i)
		{
			Enemy* enemy = new Enemy( i * 200, 0 );

			enemy->getShip().getTexture().setTexture(gShipsSprite);
			enemy->getShip().createShip(gShipsSprite.getIndex());

			enemy->setColliders();

			gEnts.push_back(enemy);
		}

		++m_wave;
	}
}

bool Wave::displayWaveNum()
{
	m_waveText.str("Wave: " + std::to_string((m_wave)));

	if (!m_waveTexture.loadFromRenderedText(m_waveText.str().c_str(), gFuturaFont, SDL_Color(0x00, 0xFF, 0x00, 0xFF)))
		return false;

	return true;
}

std::vector<Enemy>& Wave::getEnemies()
{
	return m_enemies;
}

Texture& Wave::getWaveTexture()
{
	return m_waveTexture;
}

int Wave::getWave()
{
	return m_wave;
}