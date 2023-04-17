#include "Wave.h"
#include "Globals.h"

Wave::Wave()
	: m_enemies{}
	, m_wave{}
{
	for (int i = 0; i < 4; ++i)
	{
		Enemy enemy{ i * 25, 0 };

		enemy.setTexture(gEnemyTexture);
		enemy.setCollider();

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

void Wave::render(SDL_Rect* clip, int scaleW, int scaleH, double angle, SDL_Point* centre, SDL_RendererFlip flip)
{
	for (int i = 0; i < m_enemies.size(); ++i)
	{
		SDL_Rect render_quad{ m_enemies.at(i).getPosX(), m_enemies.at(i).getPosY(), m_enemies.at(i).getTexture().getWidth(), m_enemies.at(i).getTexture().getHeight()};

		if (clip)
		{
			render_quad.w = scaleW;
			render_quad.h = scaleH;
		}

		SDL_RenderCopyEx(gWindow.getRenderer(), m_enemies.at(i).getTexture().getTexture(), clip, &render_quad, angle, centre, flip);
	}
}

void Wave::renderColliders()
{
	for (int i = 0; i < m_enemies.size(); ++i)
	{
		SDL_SetRenderDrawColor(gWindow.getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(gWindow.getRenderer(), &m_enemies.at(i).getColliders().at(0));
		SDL_RenderDrawRect(gWindow.getRenderer(), &m_enemies.at(i).getColliders().at(1));
	}
}

std::vector<Enemy>& Wave::getEnemies()
{
	return m_enemies;
}