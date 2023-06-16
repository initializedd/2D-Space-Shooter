#include "Wave.h"
#include "Common.h"

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
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(m_enemyPositions[i].x + 80, m_enemyPositions[i].y + 50);

			enemy->getShip().createShip(1);

			enemy->createColliders();

			gEnts.push_back(std::move(enemy));

			std::unique_ptr<WraithEnemy> wraithEnemy = std::make_unique<WraithEnemy>(m_enemyPositions[i].x, m_enemyPositions[i].y);

			wraithEnemy->getShip().createShip(1);

			wraithEnemy->createColliders();

			gEnts.push_back(std::move(wraithEnemy));
		}
	}
}

bool Wave::displayWaveNum()
{
	const std::string waveString = "Wave: " + std::to_string(m_currentWave);

	std::shared_ptr<Text> waveText = resourceManager.getTextSystem().findTextStream("txt_wave");
	std::shared_ptr<Font> futura = resourceManager.getTextSystem().findFont("ttf_futura");

	if (!waveText->loadFromText(waveString, futura->getFont(), SDL_Color(0x00, 0xFF, 0x00, 0xFF)))
		return false;

	waveText->getTexture()->render(0, SCREEN_HEIGHT - 150, waveText->getTexture()->getWidth(), waveText->getTexture()->getHeight(), nullptr);

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