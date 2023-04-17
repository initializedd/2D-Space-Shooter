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

	void render(SDL_Rect* clip = nullptr, int scaleW = 0, int scaleH = 0, double angle = 0.0, SDL_Point* centre = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void renderColliders();

	std::vector<Enemy>& getEnemies();
};

#endif // !WAVE_H