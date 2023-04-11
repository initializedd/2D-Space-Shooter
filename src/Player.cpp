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
	m_colliders.resize(11);

	m_colliders[0].w = 6;
	m_colliders[0].h = 1;

	m_colliders[1].w = 10;
	m_colliders[1].h = 1;

	m_colliders[2].w = 14;
	m_colliders[2].h = 1;

	m_colliders[3].w = 16;
	m_colliders[3].h = 2;

	m_colliders[4].w = 18;
	m_colliders[4].h = 2;

	m_colliders[5].w = 20;
	m_colliders[5].h = 6;

	m_colliders[6].w = 18;
	m_colliders[6].h = 2;

	m_colliders[7].w = 16;
	m_colliders[7].h = 2;

	m_colliders[8].w = 14;
	m_colliders[8].h = 1;

	m_colliders[9].w = 10;
	m_colliders[9].h = 1;

	m_colliders[10].w = 6;
	m_colliders[10].h = 1;

	shiftColliders();
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
	shiftColliders();

	// Check if outside of left screen boundary
	if (m_pos.x <= 0 || checkCollision(m_colliders, gEnemy.getColliders()))
	{
		m_pos.x = 0;
		shiftColliders();
	}
	// Check if outside of right screen boundary
	else if (m_pos.x + m_width >= SCREEN_WIDTH || checkCollision(m_colliders, gEnemy.getColliders()))
	{
		m_pos.x = SCREEN_WIDTH - m_width;
		shiftColliders();
	}

	// Update Y position based on its Y velocity
	m_pos.y += m_vel.y;
	shiftColliders();

	// Check if outside of top screen boundary
	if (m_pos.y <= 0 || checkCollision(m_colliders, gEnemy.getColliders()))
	{
		m_pos.y = 0;
		shiftColliders();
	}
	// Check if outside of bottom screen boundary
	else if (m_pos.y + m_height + m_particle.getTexture().getHeight() >= SCREEN_HEIGHT || checkCollision(m_colliders, gEnemy.getColliders()))
	{
		m_pos.y = SCREEN_HEIGHT - m_height - m_particle.getTexture().getHeight();
		shiftColliders();
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
	m_particle.getTexture().render(gPlayer.getPosX() + (gPlayer.getTexture().getWidth() / 5.6), gPlayer.getPosY() + (gPlayer.getTexture().getHeight() / 1.15), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180);

	// Middle Left Exhaust
	m_particle.getTexture().render(gPlayer.getPosX() + (gPlayer.getTexture().getWidth() / 2.9), gPlayer.getPosY() + gPlayer.getTexture().getHeight(), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180);

	// Middle Right Exhaust
	m_particle.getTexture().render(gPlayer.getPosX() + (gPlayer.getTexture().getWidth() / 1.83), gPlayer.getPosY() + gPlayer.getTexture().getHeight(), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180, nullptr, SDL_FLIP_HORIZONTAL);

	// Right Exhaust
	m_particle.getTexture().render(gPlayer.getPosX() + (gPlayer.getTexture().getWidth() / 1.41), gPlayer.getPosY() + (gPlayer.getTexture().getHeight() / 1.15), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180, nullptr, SDL_FLIP_HORIZONTAL);
}

bool Player::checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Go through the A boxes
	for (int Abox = 0; Abox < a.size(); Abox++)
	{
		//Calculate the sides of rect A
		leftA = a[Abox].x;
		rightA = a[Abox].x + a[Abox].w;
		topA = a[Abox].y;
		bottomA = a[Abox].y + a[Abox].h;

		//Go through the B boxes
		for (int Bbox = 0; Bbox < b.size(); Bbox++)
		{
			//Calculate the sides of rect B
			leftB = b[Bbox].x;
			rightB = b[Bbox].x + b[Bbox].w;
			topB = b[Bbox].y;
			bottomB = b[Bbox].y + b[Bbox].h;

			//If no sides from A are outside of B
			if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false)
			{
				//A collision is detected
				return true;
			}
		}
	}

	//If neither set of collision boxes touched
	return false;
}

void Player::shiftColliders()
{
	//The row offset
	int r = 0;

	//Go through the dot's collision boxes
	for (int set = 0; set < m_colliders.size(); ++set)
	{
		//Center the collision box
		m_colliders[set].x = m_pos.x + (getTexture().getWidth() - m_colliders[set].w) / 2;

		//Set the collision box at its row offset
		m_colliders[set].y = m_pos.y + r;

		//Move the row offset down the height of the collision box
		r += m_colliders[set].h;
	}
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

bool Player::setTexture(const char* path, const bool flag, const Uint8 red, const Uint8 green, const Uint8 blue)
{
	if (!m_texture.loadFromFile(path, flag, red, green, blue))
		return false;

	m_width = m_texture.getWidth();
	m_height = m_texture.getHeight();

	return true;
}