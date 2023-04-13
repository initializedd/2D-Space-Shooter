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
	//shiftColliders();
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
	//shiftColliders();

	// Check if outside of left screen boundary
	if (m_pos.x <= 0)
	{
		m_pos.x = 0;
		//shiftColliders();
	}
	// Check if outside of right screen boundary
	else if (m_pos.x + m_width >= SCREEN_WIDTH)
	{
		m_pos.x = SCREEN_WIDTH - m_width;
		//shiftColliders();
	}
	else if (checkCollision(m_collider, gEnemy.getCollider()))
	{
		m_pos.x -= m_vel.x;
	}

	// Update Y position based on its Y velocity
	m_pos.y += m_vel.y;
	//shiftColliders();

	// Check if outside of top screen boundary
	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		//shiftColliders();
	}
	// Check if outside of bottom screen boundary
	else if (m_pos.y + m_height + m_particle.getTexture().getHeight() >= SCREEN_HEIGHT)
	{
		m_pos.y = SCREEN_HEIGHT - m_height - m_particle.getTexture().getHeight();
		//shiftColliders();
	}
	else if (checkCollision(m_collider, gEnemy.getCollider()))
	{
		m_pos.y -= m_vel.y;
	}

	m_collider.x = m_pos.x;
	m_collider.y = m_pos.y;
}

void Player::shoot()
{
	m_weapon.shoot();
}

void Player::animateExhaust(int flameFrames)
{
	SDL_Rect* currentClip = &m_particle.getClips()[flameFrames / 6];

	// Left Exhaust
	m_particle.getTexture().render(gPlayer.getPosX() + (gPlayer.getTexture().getWidth() / 5.6), gPlayer.getPosY() + (gPlayer.getTexture().getHeight() / 1.15), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180);

	// Middle Left Exhaust
	m_particle.getTexture().render(gPlayer.getPosX() + (gPlayer.getTexture().getWidth() / 2.9), gPlayer.getPosY() + gPlayer.getTexture().getHeight(), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180);

	// Middle Right Exhaust
	m_particle.getTexture().render(gPlayer.getPosX() + (gPlayer.getTexture().getWidth() / 1.83), gPlayer.getPosY() + gPlayer.getTexture().getHeight(), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180, nullptr, SDL_FLIP_HORIZONTAL);

	// Right Exhaust
	m_particle.getTexture().render(gPlayer.getPosX() + (gPlayer.getTexture().getWidth() / 1.41), gPlayer.getPosY() + (gPlayer.getTexture().getHeight() / 1.15), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180, nullptr, SDL_FLIP_HORIZONTAL);
}

bool Player::checkCollision(SDL_Rect& a, SDL_Rect& b) 
{
	m_collider.x = m_pos.x;
	m_collider.y = m_pos.y;
	m_collider.w = m_width;
	m_collider.h = m_height;

	b.x = (SCREEN_WIDTH - gEnemy.getTexture().getWidth()) / 2;
	b.y = 0;
	b.w = gEnemy.getTexture().getWidth();
	b.h = gEnemy.getTexture().getHeight();


	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB) { return false; }

	if (topA >= bottomB) { return false; }

	if (rightA <= leftB) { return false; }

	if (leftA >= rightB) { return false; }

	return true;
}


//void Player::shiftColliders()
//{
//	//The row offset
//	int r = 0;
//
//	//Go through the dot's collision boxes
//	for (int set = 0; set < m_collider.size(); ++set)
//	{
//		//Center the collision box
//		m_collider[set].x = m_pos.x + (getTexture().getWidth() - m_collider[set].w) / 2;
//
//		//Set the collision box at its row offset
//		m_collider[set].y = m_pos.y + r;
//
//		//Move the row offset down the height of the collision box
//		r += m_collider[set].h;
//	}
//}

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

bool Player::setTexture(const char* path, const bool flag, const Uint8 red, const Uint8 green, const Uint8 blue)
{
	if (!m_texture.loadFromFile(path, flag, red, green, blue))
		return false;

	m_width = m_texture.getWidth();
	m_height = m_texture.getHeight();

	return true;
}