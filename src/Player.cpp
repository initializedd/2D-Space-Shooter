#include "Player.h"
#include "Globals.h"
#include "Constants.h"

Player::Player(int x, int y)
	: m_flameFrames{}
	, m_healthTexture{}
	, m_healthText{}
{
	m_type = PLAYER;
	m_weapon = m_type;
	
	m_id = ENTITY_ID;

	m_pos.x = x;
	m_pos.y = y;

	m_colliders.push_back(gHeadCollision);
	m_colliders.push_back(gLeftWingCollision);
	m_colliders.push_back(gRightWingCollision);
	m_colliders.push_back(gBodyCollision);
	m_colliders.push_back(gLowerCollision);
	m_colliders.push_back(gExhaustCollision);

	m_health = 1000;

	++NUM_OF_PLAYERS;
	++ENTITY_ID;
}

Player::~Player()
{
	--NUM_OF_PLAYERS;
	--ENTITY_ID;
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

void Player::update(int i)
{
	if (!isDead())
	{
		move();
		exhaustAnimation();
		getTexture().render(m_pos.x, m_pos.y);
		getWeapon().updateProjectiles();

		if (displayHealth())
			getHealhTexture().render(0, SCREEN_HEIGHT - getHealhTexture().getHeight());
	}
	else
	{
		if (deathAnimation() / 2 >= 12)
		{
			delete this;
			gEnts.erase(gEnts.begin() + i);
		}
	}
}

void Player::exhaustAnimation()
{
	SDL_Rect* currentClip = &m_particle.getClips()[m_flameFrames / 3];

	// Resize texture to fit outer exhaust dimensions
	m_particle.getTexture().scale(400 * 0.047, 400 * 0.05);

	// Left Exhaust
	m_particle.getTexture().render(m_pos.x + (m_texture.getWidth() / 6.0), m_pos.y + (m_texture.getHeight() / 1.15), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180);

	// Right Exhaust
	m_particle.getTexture().render(m_pos.x + (m_texture.getWidth() / 1.4), m_pos.y + (m_texture.getHeight() / 1.15), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180, nullptr, SDL_FLIP_HORIZONTAL);

	// Resize texture to fit middle exhaust dimensions
	m_particle.getTexture().scale(400 * 0.05, 400 * 0.05);

	// Middle Left Exhaust
	m_particle.getTexture().render(m_pos.x + (m_texture.getWidth() / 3.03), m_pos.y + m_texture.getHeight(), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180);

	// Middle Right Exhaust
	m_particle.getTexture().render(m_pos.x + (m_texture.getWidth() / 1.83), m_pos.y + m_texture.getHeight(), currentClip, m_particle.getTexture().getWidth(), m_particle.getTexture().getHeight(), 180, nullptr, SDL_FLIP_HORIZONTAL);

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

	// Player projectile pos
	m_leftProjectilePos.x = 31 + m_pos.x;
	m_leftProjectilePos.y = 0 + m_pos.y;

	m_rightProjectilePos.x = 61 + m_pos.x;
	m_rightProjectilePos.y = 1 + m_pos.y;
}