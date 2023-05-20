#include "Enemy.h"
#include "Globals.h"

Enemy::Enemy(int x, int y)
	: m_flameFrames{}
{
	m_type = ENEMY;
	m_weapon = m_type;
	m_id = ENTITY_ID;

	m_pos.x = x;
	m_pos.y = y;

	m_vel.x = ENEMY_VEL;

	m_colliders.push_back(Head1);
	m_colliders.push_back(Body1);
	m_colliders.push_back(Weapon1);
	m_colliders.push_back(Tail1);

	m_health = 100;

	gExhaustParticle.getTexture().scale(400 * 0.035, 400 * 0.035);

	++ENTITY_ID;
}

Enemy::~Enemy()
{
	--ENTITY_ID;
}

void Enemy::update(int i, double dt)
{
	getWeapon().updateProjectiles(dt);

	if (!isDead())
	{
		move(dt);
		exhaustAnimation(dt);
		//shoot(500);
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

void Enemy::render()
{
	if (!isDead())
	{
		// Left Ship Exhaust
		gExhaustParticle.getTexture().render(m_pos.x + 41, m_pos.y + 55, m_currentExhaustClip, gExhaustParticle.getTexture().getWidth(), gExhaustParticle.getTexture().getHeight(), 0, nullptr, SDL_FLIP_HORIZONTAL);

		// Right Ship Exhaust
		gExhaustParticle.getTexture().render(m_pos.x + 115, m_pos.y + 55, m_currentExhaustClip, gExhaustParticle.getTexture().getWidth(), gExhaustParticle.getTexture().getHeight());

		// Ship Texture
		m_texture.render(m_pos.x, m_pos.y, &m_texture.getClips()[m_texture.getIndex()], m_texture.getClips()[m_texture.getIndex()].w, m_texture.getClips()[m_texture.getIndex()].h, 180);
	}

	// Projejctiles
	m_weapon.renderProjectiles();

	if (isDead())
	{
		renderDeathAnimation();
	}
}

void Enemy::exhaustAnimation(double dt)
{
	m_currentExhaustClip = &gExhaustParticle.getClips()[m_flameFrames / 3];

	++m_flameFrames;
	if (m_flameFrames / 3 >= 6)
	{
		m_flameFrames = 0;
	}
}

void Enemy::setColliders()
{
	double textureRotation = 180.0;

	// Calculate the cosine and sine values of the texture's rotation angle
	double cosAngle = cos(M_PI);
	double sinAngle = sin(M_PI);

	// Calculate the centre coordinates of the rotated texture
	double textureCentreX = m_texture.getWidth()  / 2.0;
	double textureCentreY = m_texture.getHeight() / 2.0;

	for (int i = 0; i < m_colliders.size(); ++i)
	{
		// Calculate the centre coordinates of the collider
		double colliderCentreX = gShipColliders[i].w / 2.0;
		double colliderCentreY = m_colliderPositions[i].h / 2.0;

		// Translate the collider's centre to the texture's coordinate system
		double translatedX = m_colliderPositions[i].x + colliderCentreX - textureCentreX;
		double translatedY = m_colliderPositions[i].y + colliderCentreY - textureCentreY;

		// Rotate the collider's positions relative to the texture's rotation
		double rotatedX = translatedX * cosAngle - translatedY * sinAngle;
		double rotatedY = translatedX * sinAngle + translatedY * cosAngle;

		// Translate the rotated collider's positions back to the original coordinate system
		m_colliders[i].x = static_cast<int>(rotatedX + textureCentreX - colliderCentreX + m_pos.x);
		m_colliders[i].y = static_cast<int>(rotatedY + textureCentreY - colliderCentreY + m_pos.y);
	}
}

void Enemy::setCannonColliders()
{
	// Enemy left cannon pos
	m_leftCannonPos.x = 42 + m_pos.x;
	m_leftCannonPos.y = 89 + m_pos.y;

	// Enemy right cannon pos
	m_rightCannonPos.x = 70 + m_pos.x;
	m_rightCannonPos.y = 90 + m_pos.y;
}