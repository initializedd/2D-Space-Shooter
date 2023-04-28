#include "Player.h"
#include "Globals.h"
#include "Constants.h"

Player::Player(int x, int y)
	: m_flameFrames{}
	, m_healthTexture{}
	, m_healthText{}
{
	m_pos.x = x;
	m_pos.y = y;

	m_colliders.push_back(gHeadCollision);
	m_colliders.push_back(gLeftWingCollision);
	m_colliders.push_back(gRightWingCollision);
	m_colliders.push_back(gBodyCollision);
	m_colliders.push_back(gLowerCollision);
	m_colliders.push_back(gExhaustCollision);

	m_health = 1000;
}

Player::~Player()
{
}

void Player::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_UP:
			case SDLK_w:
				m_vel.y -= PLAYER_VEL;
				break;

			case SDLK_DOWN:
			case SDLK_s:
				m_vel.y += PLAYER_VEL;
				break;

			case SDLK_LEFT:
			case SDLK_a:
				m_vel.x -= PLAYER_VEL;
				break;

			case SDLK_RIGHT:
			case SDLK_d:
				m_vel.x += PLAYER_VEL;
				break;

			case SDLK_SPACE:
				shoot(250);
				break;

		}
	}
	else if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_UP:
			case SDLK_w:
				m_vel.y += PLAYER_VEL;
				break;

			case SDLK_DOWN:
			case SDLK_s:
				m_vel.y -= PLAYER_VEL;
				break;

			case SDLK_LEFT:
			case SDLK_a:
				m_vel.x += PLAYER_VEL;
				break;

			case SDLK_RIGHT:
			case SDLK_d:
				m_vel.x -= PLAYER_VEL;
				break;
		}
	}
}

void Player::move()
{
	// Update X position based on its X velocity
	m_pos.x += m_vel.x;
	setColliders();

	// Check if outside of left screen boundary
	if (m_pos.x <= 0)
	{
		m_pos.x = 0;
		setColliders();
	}
	// Check if outside of right screen boundary
	else if (m_pos.x + m_texture.getWidth() >= SCREEN_WIDTH)
	{
		m_pos.x = SCREEN_WIDTH - m_texture.getWidth();
		setColliders();
	}
	// Check for collision on X axis
	else if (checkCollisionPosX(gWave.getEnemies()))
	{
		setColliders();
	}

	// Update Y position based on its Y velocity
	m_pos.y += m_vel.y;
	setColliders();

	// Check if outside of top screen boundary
	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		setColliders();
	}
	// Check if outside of bottom screen boundary
	else if (m_pos.y + m_texture.getHeight() + m_particle.getTexture().getHeight() >= SCREEN_HEIGHT)
	{
		m_pos.y = SCREEN_HEIGHT - m_texture.getHeight() - m_particle.getTexture().getHeight();
		setColliders();
	}
	// Check for collision on Y axis
	else if (checkCollisionPosY(gWave.getEnemies()))
	{
		setColliders();
	}
}

bool Player::checkCollisionPosX(std::vector<Enemy>& enemies)
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		for (int j = 0; j < this->m_colliders.size(); ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				if (SDL_HasIntersection(&m_colliders[j], &enemies.at(i).getColliders().at(k)))
				{
					if (m_pos.x <= enemies.at(i).getPosX())
						m_pos.x = (enemies.at(i).getPosX() - (enemies.at(i).getPosX() - enemies.at(i).getColliders().at(k).x)) - ((m_colliders[j].x - m_pos.x) + m_colliders[j].w);

					if (m_pos.x > enemies.at(i).getPosX())
						m_pos.x = (enemies.at(i).getColliders().at(k).x + enemies.at(i).getColliders().at(k).w) - (m_colliders[j].x - m_pos.x);

					return true;
				}
			}
		}
	}

	return false;
}

bool Player::checkCollisionPosY(std::vector<Enemy>& enemies)
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		for (int j = 0; j < this->m_colliders.size(); ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				if (SDL_HasIntersection(&m_colliders[j], &enemies.at(i).getColliders().at(k)))
				{
					if (m_pos.y <= enemies.at(i).getPosY())
						m_pos.y = (enemies.at(i).getPosY() - (enemies.at(i).getPosY() - enemies.at(i).getColliders().at(k).y)) - ((m_colliders[j].y - m_pos.y) + m_colliders[j].h);

					if (m_pos.y > enemies.at(i).getPosY())
						m_pos.y = (enemies.at(i).getColliders().at(k).y + enemies.at(i).getColliders().at(k).h) - (m_colliders[j].y - m_pos.y);

					return true;
				}
			}
		}
	}

	return false;
}

void Player::exhaustAnimation()
{
	SDL_Rect* currentClip = &m_particle.getClips()[m_flameFrames / 3];

	// Resize texture to fit outer exhaust dimensions
	m_particle.getTexture().resize(400 * 0.047, 400 * 0.05);

	// Left Exhaust
	m_particle.getTexture().render(this->getPosX() + (this->getTexture().getWidth() / 6.0), this->getPosY() + (this->getTexture().getHeight() / 1.15), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180);

	// Right Exhaust
	m_particle.getTexture().render(this->getPosX() + (this->getTexture().getWidth() / 1.4), this->getPosY() + (this->getTexture().getHeight() / 1.15), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180, nullptr, SDL_FLIP_HORIZONTAL);

	// Resize texture to fit middle exhaust dimensions
	m_particle.getTexture().resize(400 * 0.05, 400 * 0.05);

	// Middle Left Exhaust
	m_particle.getTexture().render(this->getPosX() + (this->getTexture().getWidth() / 3.03), this->getPosY() + this->getTexture().getHeight(), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180);

	// Middle Right Exhaust
	m_particle.getTexture().render(this->getPosX() + (this->getTexture().getWidth() / 1.83), this->getPosY() + this->getTexture().getHeight(), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180, nullptr, SDL_FLIP_HORIZONTAL);

	++m_flameFrames;
	if (m_flameFrames / 3 >= 6)
	{
		m_flameFrames = 0;
	}
}

bool Player::displayHealth()
{
	if (m_health > 0)
		m_healthText.str("Health: " + std::to_string((m_health)));
	else
		m_healthText.str("Dead");

	if (!m_healthTexture.loadFromRenderedText(m_healthText.str().c_str(), gFuturaFont, SDL_Color(0x00, 0xFF, 0x00, 0xFF)))
		return false;

	return true;
}

Texture& Player::getHealhTexture()
{
	return m_healthTexture;
}

void Player::setColliders()
{
	m_colliders[0].x = gHeadCollision.x + m_pos.x;
	m_colliders[0].y = gHeadCollision.y + m_pos.y;

	m_colliders[1].x = gLeftWingCollision.x + m_pos.x;
	m_colliders[1].y = gLeftWingCollision.y + m_pos.y;

	m_colliders[2].x = gRightWingCollision.x + m_pos.x;
	m_colliders[2].y = gRightWingCollision.y + m_pos.y;

	m_colliders[3].x = gBodyCollision.x + m_pos.x;
	m_colliders[3].y = gBodyCollision.y + m_pos.y;

	m_colliders[4].x = gLowerCollision.x + m_pos.x;
	m_colliders[4].y = gLowerCollision.y + m_pos.y;

	m_colliders[5].x = gExhaustCollision.x + m_pos.x;
	m_colliders[5].y = gExhaustCollision.y + m_pos.y;

	m_leftCannonPos.x = 31 + m_pos.x;
	m_leftCannonPos.y = 0 + m_pos.y;

	m_rightCannonPos.x = 61 + m_pos.x;
	m_rightCannonPos.y = 1 + m_pos.y;
}