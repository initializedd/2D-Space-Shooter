#include "Player.h"
#include "Globals.h"
#include "Constants.h"

Player::Player()
	: m_texture{}
	, m_width{}
	, m_height{}
	, m_pos{}
	, m_vel{}
	, m_collider{}
	, m_health{}
	, m_particle{}
	, m_weapon{}
{
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
	setCollider();

	// Check if outside of left screen boundary
	if (m_pos.x <= 0)
	{
		m_pos.x = 0;
		setCollider();
	}
	// Check if outside of right screen boundary
	else if (m_pos.x + m_collider.w >= SCREEN_WIDTH)
	{
		m_pos.x = SCREEN_WIDTH - m_collider.w;
		setCollider();

	}
	// Check if collision on X axis
	else if (checkCollision(gEnemy.getCollider()))
	{
		if (m_pos.x < gEnemy.getPosX())
			m_pos.x = gEnemy.getPosX() - m_collider.w;

		else if (m_pos.x > gEnemy.getPosX())
			m_pos.x = gEnemy.getPosX() + gEnemy.getTexture().getWidth();

		setCollider();
	}

	// Update Y position based on its Y velocity
	m_pos.y += m_vel.y;
	setCollider();

	// Check if outside of top screen boundary
	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		setCollider();
	}
	// Check if outside of bottom screen boundary
	else if (m_pos.y + m_collider.h >= SCREEN_HEIGHT)
	{
		m_pos.y = SCREEN_HEIGHT - m_collider.h;
		setCollider();
	}
	// Check if collision on Y axis
	else if (checkCollision(gEnemy.getCollider()))
	{
		if (m_pos.y < gEnemy.getPosY())
			m_pos.y = gEnemy.getPosY() - m_collider.h;

		else if (m_pos.y > gEnemy.getPosY())
			m_pos.y = gEnemy.getPosY() + gEnemy.getTexture().getHeight();

		setCollider();
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

bool Player::checkCollision(SDL_Rect& box)
{
	this->setCollider();

	return SDL_HasIntersection(&this->getCollider(), &box);
}

SDL_Rect& Player::getCollider()
{
	return m_collider;
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

void Player::setCollider()
{
	m_collider.x = m_pos.x;
	m_collider.y = m_pos.y;
	m_collider.w = m_texture.getWidth();
	m_collider.h = m_texture.getHeight() + m_particle.getTexture().getHeight();
}