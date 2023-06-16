#include "Player.h"
#include "Common.h"

Player::Player(int x, int y)
	: m_ability{}
	, m_abilityFrames{}
	, m_currentAbilityClip{}
	, m_shieldActivated{}
	, m_hasAbility{}
	, m_ui{}
	, m_flameFrames{}
	, m_healthTexture{}
	, m_healthText{}
	, m_shieldTexture{}
	, m_shieldText{}
{
	m_type = PLAYER;
	m_weapon = { m_type, Vector2<float>(0, -1) };

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
		handlePickUpCollision(gPickUp);
		exhaustAnimation();
		healthAnimation();
		//shieldAnimation();
	}
	else
	{
		if (deathAnimation() && m_weapon.getProjectiles().empty())
		{
			gEnts.erase(gEnts.begin() + i);
		}
	}
}

void Player::render()
{
	if (!isDead())
	{
		m_ui.displayHealth(m_health);
		m_ui.displayShield(m_shield);

		std::shared_ptr<Sprite> fireSprite = resourceManager.getTextureSystem().findSprite("sprite_fire");

		// Exhaust Textures
		for (int i = 0; i < m_ship.getParts().size(); ++i)
		{
			ShipPart& part = m_ship.getParts()[i];
			const SDL_Rect& collider = part.getCollider().getRect();

			if (part.getPartType() == LEFT_EXHAUST || part.getPartType() == RIGHT_EXHAUST)
			{
				fireSprite->render(collider.x, collider.y, collider.w, collider.h, m_currentExhaustClip, 180);
			}
			else if (part.getPartType() == EXHAUST)
			{
				fireSprite->render(collider.x, collider.y, collider.w, collider.h, m_currentExhaustClip, 180);
				fireSprite->render(collider.x, collider.y, collider.w, collider.h, m_currentExhaustClip, 180,
					nullptr, SDL_FLIP_HORIZONTAL);
			}
		}

		// Ship Texture
		std::shared_ptr<Sprite> ship = resourceManager.getTextureSystem().findSprite("sprite_ships");

		ship->render(m_pos.x, m_pos.y, 64, 80, &ship->getClips()[m_ship.getIndex()]);

		renderHealthAnimation();
		renderShieldAnimation();
	}

	// Projejctiles
	m_weapon.renderProjectiles();

	if (isDead())
	{
		renderDeathAnimation();
	}
}

void Player::handlePickUpCollision(std::vector<PickUp>& pickUp)
{
	if (!pickUp.empty())
	{
		for (int i = 0; i < m_ship.getParts().size(); ++i)
		{
			for (int j = 0; j < gPickUp.size(); ++j)
			{
				if (m_ship.getParts()[i].getCollider().intersects(pickUp[j].getItem().collider))
				{
					m_ability = pickUp[j].getAbility();
					m_hasAbility = true;
					createHealth();
					pickUp.erase(pickUp.begin() + j);
					continue;
				}

				if (pickUp[j].getItem().collider.getRect().y > SCREEN_HEIGHT)
					pickUp.erase(pickUp.begin() + j);
			}
		}
	}
}

void Player::healthAnimation()
{
	if (m_hasAbility)
	{
		if (m_abilityFrames / 2 <= 16)
		{
			std::shared_ptr<Sprite> healthSprite = resourceManager.getTextureSystem().findSprite("sprite_health_regen");
			m_currentAbilityClip = &healthSprite->getClips()[m_abilityFrames / 2];
			++m_abilityFrames;
		}
	}
}

void Player::shieldAnimation()
{
	if (m_shield > 0)
	{
		std::shared_ptr<Sprite> shieldSprite = resourceManager.getTextureSystem().findSprite("sprite_blue_shield");
		m_currentAbilityClip = &shieldSprite->getClips()[m_abilityFrames / 3];

		++m_abilityFrames;
		if (m_abilityFrames / 3 >= 11)
		{
			m_abilityFrames = 0;
		}
	}
}

bool Player::renderHealthAnimation()
{
	if (!m_hasAbility)
		return false;

	std::shared_ptr<Sprite> ship = resourceManager.getTextureSystem().findSprite("sprite_ships");
	std::shared_ptr<Sprite> healthSprite = resourceManager.getTextureSystem().findSprite("sprite_health_regen");

	int abilityPosX = (m_pos.x + ship->getClips()[m_ship.getIndex()].w / 4) - m_currentAbilityClip->w / 2;
	int abilityPosY = (m_pos.y + ship->getClips()[m_ship.getIndex()].h / 4) - m_currentAbilityClip->h / 2;

	healthSprite->render(abilityPosX, abilityPosY, m_currentAbilityClip->w, m_currentAbilityClip->h, m_currentAbilityClip);

	return true;
}

bool Player::renderShieldAnimation()
{
	if (!m_shieldActivated)
		return false;

	std::shared_ptr<Sprite> ship = resourceManager.getTextureSystem().findSprite("sprite_ships");
	std::shared_ptr<Sprite> shieldSprite = resourceManager.getTextureSystem().findSprite("sprite_blue_shield");

	int abilityPosX = (m_pos.x + ship->getClips()[m_ship.getIndex()].w / 4) - m_currentAbilityClip->w / 2;
	int abilityPosY = (m_pos.y + ship->getClips()[m_ship.getIndex()].h / 4) - m_currentAbilityClip->h / 2;

	shieldSprite->render(abilityPosX, abilityPosY, m_currentAbilityClip->w, m_currentAbilityClip->h, m_currentAbilityClip);

	return true;
}

void Player::createHealth()
{
	m_ability.createAbility();
	int bonusHealth = m_ability.getValue();

	if (bonusHealth + m_health <= 1000)
		m_health += bonusHealth;
	else
		m_health = 1000;
}

void Player::createShield()
{
	m_ability.createAbility();
	int bonusShield = m_ability.getValue();

	if (bonusShield + m_shield <= 200)
		m_shield += bonusShield;
	else
		m_shield = 200;
}

Ability& Player::getAbility()
{
	return m_ability;
}

UI& Player::getUI()
{
	return m_ui;
}

void Player::setShield(int shield)
{
	m_shield = shield;
}