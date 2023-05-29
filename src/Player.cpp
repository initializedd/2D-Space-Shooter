#include "Player.h"
#include "Globals.h"
#include "Constants.h"

Player::Player(int x, int y)
	: m_ability{SHIELD}
	, m_abilityFrames{}
	, m_currentAbilityClip{}
	, m_shieldActivated{}
	, m_flameFrames{}
	, m_healthTexture{}
	, m_healthText{}
	, m_shieldTexture{}
	, m_shieldText{}
{
	m_type = PLAYER;
	m_weapon = { m_type, Vector2<float>(0, -1)};
	
	m_pos.x = x;
	m_pos.y = y;

	m_health = 1000;

	m_speed = PLAYER_SPEED;

	++NUM_OF_PLAYERS;
}

Player::~Player()
{
	--NUM_OF_PLAYERS;
}

void Player::handleEvent(SDL_Event& event)
{
	// Get the state of the keyboard
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	// Handle vertical movement
	if (keyboardState[SDL_SCANCODE_UP] || keyboardState[SDL_SCANCODE_W])
	{
		// Move upward
		m_direction.y = -1;
	}
	else if (keyboardState[SDL_SCANCODE_DOWN] || keyboardState[SDL_SCANCODE_S])
	{
		// Move downward
		m_direction.y = 1;
	}
	else
	{
		// No vertical movement
		m_direction.y = 0;
	}

	// Handle horizontal movement
	if (keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A])
	{
		// Move left
		m_direction.x = -1;
	}
	else if (keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D])
	{
		// Move right
		m_direction.x = 1;
	}
	else
	{
		// No horizontal movement
		m_direction.x = 0;
	}

	// Calculate the velocity based on the direction and speed
	m_movement.calculateVelocity(m_direction, PLAYER_SPEED);

	// Shoot if the spacebar is pressed
	if (keyboardState[SDL_SCANCODE_SPACE])
	{
		shoot(250);
	}
}


void Player::update(int i, double dt)
{
	getWeapon().updateProjectiles(dt);
	
	if (!isDead())
	{
		move(dt);
		exhaustAnimation();
		shieldAnimation();
	}
	else
	{
		if (deathAnimation() && m_weapon.getProjectiles().empty())
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

		if (displayHealth())
			m_healthTexture.render(0, SCREEN_HEIGHT - m_shieldTexture.getHeight());

		if (displayShield())
			m_shieldTexture.render(200, SCREEN_HEIGHT - m_shieldTexture.getHeight());

		if (m_shieldActivated)
			m_ability.getParticle().getTexture().render(m_pos.x - 32, m_pos.y - 40, m_currentAbilityClip, 128, 160);
	}

	// Projejctiles
	m_weapon.renderProjectiles();

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
	{
		m_shieldText.str("Shield: " + std::to_string(m_shield));
		m_shieldActivated = true;
	}
	else
	{
		m_shieldText.str("Shield: " + std::to_string(0));
		m_shieldActivated = false;
	}

	if (!m_shieldTexture.loadFromRenderedText(m_shieldText.str().c_str(), gFuturaFont, SDL_Color(0x00, 0xFF, 0x00, 0xFF)))
		return false;

		return true;
}

void Player::shieldAnimation()
{
	m_currentAbilityClip = &m_ability.getParticle().getTexture().getClips()[m_abilityFrames / 3];

	++m_abilityFrames;
	if (m_abilityFrames / 3 >= 11)
	{
		m_abilityFrames = 0;
	}
}

void Player::createShield()
{
	m_ability.createAbility();
	m_shield = m_ability.getValue();
}

Ability& Player::getAbility()
{
	return m_ability;
}

void Player::setShield(int shield)
{
	m_shield = shield;
}