#include "Entity.h"
#include "Constants.h"

Entity::Entity()
	: m_texture{}
	, m_width{}
	, m_height{}
	, m_posX{}
	, m_posY{}
	, m_velX{}
	, m_velY{}
	, m_health{}
{
}

Entity::~Entity()
{
	m_texture.free();
}

void Entity::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_UP:
			case SDLK_w:
				m_velY -= ENTITY_VEL;
				break;

			case SDLK_DOWN:
			case SDLK_s:
				m_velY += ENTITY_VEL;
				break;

			case SDLK_LEFT:
			case SDLK_a:
				m_velX -= ENTITY_VEL;
				break;

			case SDLK_RIGHT:
			case SDLK_d:
				m_velX += ENTITY_VEL;
				break;

			case SDLK_SPACE:
				shoot();
				break;
		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_UP:
			case SDLK_w:
				m_velY += ENTITY_VEL;
				break;

			case SDLK_DOWN:
			case SDLK_s:
				m_velY -= ENTITY_VEL;
				break;

			case SDLK_LEFT:
			case SDLK_a:
				m_velX += ENTITY_VEL;
				break;

			case SDLK_RIGHT:
			case SDLK_d:
				m_velX -= ENTITY_VEL;
				break;
		}
	}
}

void Entity::move()
{
	// Update X position based on its X velocity
	m_posX += m_velX;

	// Check if outside of left screen boundary
	if (m_posX <= 0)
	{
		m_posX = 0;
	}
	// Check if outside of right screen boundary
	else if (m_posX + m_width >= SCREEN_WIDTH)
	{
		m_posX = SCREEN_WIDTH - m_width;
	}

	// Update Y position based on its Y velocity
	m_posY += m_velY;

	// Check if outside of top screen boundary
	if (m_posY <= 0)
	{
		m_posY = 0;
	}
	// Check if outside of bottom screen boundary
	else if (m_posY + m_height >= SCREEN_HEIGHT)
	{
		m_posY = SCREEN_HEIGHT - m_height;
	}
}

bool Entity::setTexture(const char* path, const bool flag, const Uint8 red, const Uint8 green, const Uint8 blue)
{
	if (!m_texture.loadFromFile(path, flag, red, green, blue))
		return false;

	m_width = m_texture.getWidth();
	m_height = m_texture.getHeight();

	return true;
}

Texture& Entity::getTexture()
{
	return m_texture;
}

int Entity::getPosX()
{
	return m_posX;
}

int Entity::getPosY()
{
	return m_posY;
}