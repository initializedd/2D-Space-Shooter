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
		int last = m_colliders.size() - 1;
		m_particle.getTexture().scale(m_colliders[last].w, m_colliders[last].h);

		//Exhaust Texture
		m_particle.getTexture().render(m_colliders[last].x, m_colliders[last].y, m_currentExhaustClip, m_colliders[last].w, m_colliders[last].h, 180);
		m_particle.getTexture().render(m_colliders[last].x, m_colliders[last].y, m_currentExhaustClip, m_colliders[last].w, m_colliders[last].h, 180, nullptr, SDL_FLIP_HORIZONTAL);

		// Ship Texture
		m_texture.render(m_pos.x, m_pos.y, &m_texture.getClips()[m_texture.getIndex()], m_texture.getClips()[m_texture.getIndex()].w, m_texture.getClips()[m_texture.getIndex()].h);
	}

	// Projejctiles
	m_weapon.renderProjectiles();

	if (displayHealth())
		getHealhTexture().render(0, SCREEN_HEIGHT - getHealhTexture().getHeight());

	if (isDead())
	{
		renderDeathAnimation();
	}
}

void Player::exhaustAnimation(double dt)
{
	m_currentExhaustClip = &m_particle.getClips()[m_flameFrames / 3];

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
	double textureRotation = 0.0;
	double textureRadians = textureRotation * (M_PI / 180.0);

	// Calculate the cosine and sine values of the texture's rotation angle
	double cosAngle = cos(textureRadians);
	double sinAngle = sin(textureRadians);

	// Calculate the centre coordinates of the rotated texture
	double textureCentreX = m_texture.getWidth() / 2.0;
	double textureCentreY = m_texture.getHeight() / 2.0;

	for (int i = 0; i < m_colliders.size(); ++i)
	{
		// Calculate the centre coordinates of the collider
		double colliderCentreX = gShipColliders[m_texture.getIndex()][i].w / 2.0;
		double colliderCentreY = gShipColliders[m_texture.getIndex()][i].h / 2.0;

		// Translate the collider's centre to the texture's coordinate system
		double translatedX = gShipColliders[m_texture.getIndex()][i].x + colliderCentreX - textureCentreX;
		double translatedY = gShipColliders[m_texture.getIndex()][i].y + colliderCentreY - textureCentreY;

		// Rotate the collider's positions relative to the texture's rotation
		double rotatedX = translatedX * cosAngle - translatedY * sinAngle;
		double rotatedY = translatedX * sinAngle + translatedY * cosAngle;

		// Translate the rotated collider's positions back to the original coordinate system
		m_colliders[i].x = static_cast<int>(rotatedX + textureCentreX - colliderCentreX + m_pos.x);
		m_colliders[i].y = static_cast<int>(rotatedY + textureCentreY - colliderCentreY + m_pos.y);
	}
}

void Player::setCannonColliders()
{
	// Player left cannon pos
	m_leftCannonPos.x = 31 + m_pos.x;
	m_leftCannonPos.y = 0 + m_pos.y;

	// Player right cannon pos
	m_rightCannonPos.x = 61 + m_pos.x;
	m_rightCannonPos.y = 1 + m_pos.y;
}