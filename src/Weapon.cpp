#include "Weapon.h"
#include "Globals.h"
#include "Constants.h"

Weapon::Weapon(EntityType ownerType)
	: m_ownerType{ ownerType }
	, m_name{}
	, m_damage{}
	, m_projectiles{}
	, m_lastShot{}
{
}

Weapon::~Weapon()
{
}

void Weapon::shoot(Pair<int> leftProjectilePos, Pair<int> rightProjectilePos, unsigned int delay)
{
	if (!m_lastShot.isStarted())
	{
		m_lastShot.start();
	}
	else if (m_lastShot.getTicks() < delay)
	{
		return; // not enough time has passed
	}
	m_lastShot.start();

	Projectile leftProjectile{};
	leftProjectile.setPos(leftProjectilePos);
	leftProjectile.setType(LEFT_PROJECTILE);
	leftProjectile.setCollider(gLeftProjectileHitBox);

	m_projectiles.push_back(leftProjectile);

	Projectile rightProjectile{};
	rightProjectile.setPos(rightProjectilePos);
	rightProjectile.setType(RIGHT_PROJECTILE);
	rightProjectile.setCollider(gRightProjectileHitBox);

	m_projectiles.push_back(rightProjectile);

	gProjectileSound.playChunk(-1, 0, 100);
}

void Weapon::updateProjectiles()
{
	if (!m_projectiles.empty())
	{
		int velocity{};
		int offset{};
		bool (*comparisonPtr)(int, int) { nullptr };

		switch (m_ownerType)
		{
			case PLAYER:
				velocity = LASER_VEL;
				comparisonPtr = &isless;
				offset = 0 - gProjectileTexture.getHeight();
				break;

			case ENEMY:
				velocity = -LASER_VEL;
				comparisonPtr = &isgreater;
				offset = SCREEN_HEIGHT;
				break;
		}

		for (int i = 0; i < m_projectiles.size(); ++i)
		{
			m_projectiles[i].updateCollider();

			if (comparisonPtr && comparisonPtr(m_projectiles[i].getPosY(), offset) || m_projectiles[i].checkCollision(gEnts, m_ownerType))
			{
				m_projectiles.erase(m_projectiles.begin() + i);

				break;
			}
			else
			{
				gProjectileTexture.render(m_projectiles[i].getPosX(), m_projectiles[i].getPosY(), &gRedProjectileClip, gRedProjectileClip.w, gRedProjectileClip.h, 90);

				#if defined(_DEBUG)
				// Projectile Debug Info
				m_projectiles[i].debug();
				#endif

				m_projectiles[i].move(velocity);
			}

		}
	}
}

std::string& Weapon::getName()
{
	return m_name;
}

std::vector<Projectile>& Weapon::getProjectiles()
{
	return m_projectiles;
}

int Weapon::getDamage() const
{
	return m_damage;
}