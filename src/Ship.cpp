#include "Ship.h"

Ship::Ship()
	: m_texture{}
	, m_clips{}
	//, m_weapon{}
	, m_exhaustParticle{}
	, m_leftProjectilePos{}
	, m_rightProjectilePos{}
{
	std::string dir{ "C:/Users/Brian/Desktop/2D Space Shooter/2D-Space-Shooter/bin/" };
	m_texture.loadFromFile((dir + "img/player_ships_sprite.png").c_str(), false);

	setClipsFromSprite(128, 160, 40, 33);
}

Ship::~Ship()
{
}

void Ship::setClipsFromSprite(int width, int height, int padding, int elements)
{
	for (int i = 0; i < elements; ++i)
	{
		m_clips[i].x = i * (width + padding) + (padding / 2);
		m_clips[i].y = padding / 2;
		m_clips[i].w = width;
		m_clips[i].h = height;
	}
}

Texture& Ship::getTexture()
{
	return m_texture;
}

SDL_Rect[] Ship::getClips()
{
	return m_clips;
}