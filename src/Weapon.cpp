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

void Weapon::shoot(Pair<int> leftCannonPos, Pair<int> rightCannonPos, unsigned int delay)
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
	leftProjectile.setPos(leftCannonPos);
	leftProjectile.setType(LEFT_PROJECTILE);
	leftProjectile.updateCollider();

	m_projectiles.push_back(leftProjectile);

	Projectile rightProjectile{};
	rightProjectile.setPos(rightCannonPos);
	rightProjectile.setType(RIGHT_PROJECTILE);
	rightProjectile.updateCollider();

	m_projectiles.push_back(rightProjectile);

	gProjectileSound.playChunk(-1, 0, 100);
}

void Weapon::updateProjectiles(double dt)
{
	if (!m_projectiles.empty())
	{
		int velocity{};

		switch (m_ownerType)
		{
			case PLAYER:
				velocity = LASER_VEL;
				break;

			case ENEMY:
				velocity = -LASER_VEL;
				break;
		}

		for (int i = 0; i < m_projectiles.size(); ++i)
		{
			if (m_projectiles[i].checkScreenBoundary() || m_projectiles[i].checkCollision(gEnts, m_ownerType))
			{
				m_projectiles.erase(m_projectiles.begin() + i);
				break;
			}
			else
			{
				m_projectiles[i].move(velocity, dt);
				m_projectiles[i].updateCollider();
			}
		}
	}
}

void Weapon::renderProjectiles()
{
	if (!m_projectiles.empty())
	{
		for (int i = 0; i < m_projectiles.size(); ++i)
		{
			gProjectileTexture.render(m_projectiles[i].getPosX(), m_projectiles[i].getPosY(), &gRedProjectileClip, gRedProjectileClip.w, gRedProjectileClip.h, 90);
			
			#if defined(_DEBUG)
			// Projectile Debug Info
			m_projectiles[i].debug();
			#endif
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