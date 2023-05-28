#include "Player.h"
#include "Globals.h"
#include "Constants.h"

Player::Player(int x, int y)
	: m_ability{SHIELD}
	, m_flameFrames{}
	, m_healthTexture{}
	, m_healthText{}
	, m_shieldTexture{}
	, m_shieldText{}
{
	m_type = PLAYER;
	m_weapon = { m_type, Vector2<float>(0, -1)};

	m_direction = Vector2<float>(0, -1);
	
	m_pos.x = x;
	m_pos.y = y;
	
	m_health = 1000;

	++NUM_OF_PLAYERS;
}

Player::~Player()
{
	--NUM_OF_PLAYERS;
}

void Player::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.sym)
		{
			case SDLK_UP:
			case SDLK_w:
				m_vel.y -= PLAYER_SPEED;
				break;

			case SDLK_DOWN:
			case SDLK_s:
				m_vel.y += PLAYER_SPEED;
				break;

			case SDLK_LEFT:
			case SDLK_a: 
				m_vel.x -= PLAYER_SPEED;
				break;

			case SDLK_RIGHT:
			case SDLK_d:
				m_vel.x += PLAYER_SPEED;
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
				m_vel.y += PLAYER_SPEED;
				break;

			case SDLK_DOWN:
			case SDLK_s:
				m_vel.y -= PLAYER_SPEED;
				break;

			case SDLK_LEFT:
			case SDLK_a:
				m_vel.x += PLAYER_SPEED;
				break;

			case SDLK_RIGHT:
			case SDLK_d:
				m_vel.x -= PLAYER_SPEED;
				break;
		}
	}
}

void Player::update(int i, double dt)
{
	getWeapon().updateProjectiles(dt);
	
	if (!isDead())
	{
		move(dt);
		exhaustAnimation(dt);
	}
	else
	{
		if (deathAnimation(dt) && m_weapon.getProjectiles().empty())
		{
			delete this;
			gEnts.erase(gEnts.begin() + i);
		}
	}
}

void Player::render()
{
	if (!isDead())
	{
		// Exhaust Textures
		for (int i = 0; i < m_ship.getParts().size(); ++i)
		{
			ShipPart& part = m_ship.getParts()[i];
			SDL_Rect& collider = part.getCollider().getRect();

			if (part.getPartType() == LEFT_EXHAUST || part.getPartType() == RIGHT_EXHAUST)
			{
				gExhaustParticle.getTexture().render(collider.x, collider.y, m_currentExhaustClip, collider.w, collider.h, 180);
			}
			else if (part.getPartType() == EXHAUST)
			{
				gExhaustParticle.getTexture().render(collider.x, collider.y, m_currentExhaustClip, collider.w, collider.h, 180);
				gExhaustParticle.getTexture().render(collider.x, collider.y, m_currentExhaustClip, collider.w, collider.h, 180, nullptr, SDL_FLIP_HORIZONTAL);
			}
		}

		// Ship Texture
		m_ship.getTexture().render(m_pos.x, m_pos.y, &m_ship.getTexture().getClips()[m_ship.getTexture().getIndex()], 64, 80);
	}

	// Projejctiles
	m_weapon.renderProjectiles();

	if (displayHealth())
		m_healthTexture.render(0, SCREEN_HEIGHT - m_shieldTexture.getHeight());

	if (displayShield())
		m_shieldTexture.render(20, SCREEN_HEIGHT - m_shieldTexture.getHeight());

	if (isDead())
	{
		renderDeathAnimation();
	}
}

bool Player::displayHealth()
{
	if (m_health > 0)
		m_healthText.str("Health: " + std::to_string(m_health));
	else
		m_healthText.str("Dead");

	if (!m_healthTexture.loadFromRenderedText(m_healthText.str().c_str(), gFuturaFont, SDL_Color(0x00, 0xFF, 0x00, 0xFF)))
		return false;

	return true;
}

bool Player::displayShield()
{
	if (m_shield > 0)
		m_shieldText.str("Shield: " + std::to_string(m_shield));
	else
		m_shieldText.str("Shiled: " + std::to_string(0));

	if (!m_shieldTexture.loadFromRenderedText(m_shieldText.str().c_str(), gFuturaFont, SDL_Color(0x00, 0x00, 0xFF, 0xFF)))
		return false;

		return true;
}

Ability& Player::getAbility()
{
	return m_ability;
}

void Player::setShield(int shield)
{
	m_shield = shield;
}