#include "Player.h"
#include "Globals.h"
#include "Constants.h"

Player::Player()
	: m_texture{}
	, m_width{}
	, m_height{}
	, m_pos{}
	, m_vel{}
	, m_colliders{}
	, m_health{}
	, m_particle{}
	, m_weapon{}
{
	m_colliders.push_back(gHeadCollision);
	m_colliders.push_back(gLeftWingCollision);
	m_colliders.push_back(gRightWingCollision);
	m_colliders.push_back(gBodyCollision);
	m_colliders.push_back(gLowerCollision);
	m_colliders.push_back(gExhaustCollision);
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
	// Check if collision on X axis
	else if (checkCollisionPosX(gEnemy.getColliders()))
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
	// Check if collision on Y axis
	else if (checkCollisionPosY(gEnemy.getColliders()))
	{
		setColliders();
	}
}

void Player::shoot()
{
	m_weapon.shoot();
}

void Player::animateExhaust(int flameFrames)
{
	SDL_Rect* currentClip = &m_particle.getClips()[flameFrames / 6];

	// Left Exhaust
	m_particle.getTexture().render(this->getPosX() + (this->getTexture().getWidth() / 5.6), this->getPosY() + (this->getTexture().getHeight() / 1.15), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180);

	// Middle Left Exhaust
	m_particle.getTexture().render(this->getPosX() + (this->getTexture().getWidth() / 2.9), this->getPosY() + this->getTexture().getHeight(), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180);

	// Middle Right Exhaust
	m_particle.getTexture().render(this->getPosX() + (this->getTexture().getWidth() / 1.83), this->getPosY() + this->getTexture().getHeight(), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180, nullptr, SDL_FLIP_HORIZONTAL);

	// Right Exhaust
	m_particle.getTexture().render(this->getPosX() + (this->getTexture().getWidth() / 1.41), this->getPosY() + (this->getTexture().getHeight() / 1.15), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180, nullptr, SDL_FLIP_HORIZONTAL);
}

bool Player::checkCollisionPosX(std::vector<SDL_Rect>& box)
{
	for (int i = 0; i < box.size(); ++i)
	{
		for (int j = 0; j < this->m_colliders.size(); ++j)
		{
			if (SDL_HasIntersection(&m_colliders[j], &box.at(i)))
			{
				if (m_pos.x <= gEnemy.getPosX())
					m_pos.x = (gEnemy.getPosX() - (gEnemy.getPosX() - box.at(i).x)) - ((m_colliders[j].x - m_pos.x) + m_colliders[j].w);

				if (m_pos.x > gEnemy.getPosX())
					m_pos.x = (box.at(i).x + box.at(i).w) - (m_colliders[j].x - m_pos.x);

				return true;
			}
		}
	}

	return false;
}

bool Player::checkCollisionPosY(std::vector<SDL_Rect>& box)
{
	for (int i = 0; i < box.size(); ++i)
	{
		for (int j = 0; j < this->m_colliders.size(); ++j)
		{
			if (SDL_HasIntersection(&m_colliders[j], &box.at(i)))
			{
				if (m_pos.y <= gEnemy.getPosY())
					m_pos.y = (gEnemy.getPosY() - (gEnemy.getPosY() - box.at(i).y)) - ((m_colliders[j].y - m_pos.y) + m_colliders[j].h);

				if (m_pos.y > gEnemy.getPosY())
					m_pos.y = (box.at(i).y + box.at(i).h) - (m_colliders[j].y - m_pos.y);

				return true;
			}
		}
	}

	return false;
}

std::vector<SDL_Rect>& Player::getColliders()
{
	return m_colliders;
}

Texture& Player::getTexture()
{
	return m_texture;
}

Particle& Player::getParticle()
{
	return m_particle;
}

Weapon& Player::getWeapon()
{
	return m_weapon;
}

int Player::getPosX() const
{
	return m_pos.x;
}

int Player::getPosY() const
{
	return m_pos.y;
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
}