#include "Weapon.h"
#include "Globals.h"
#include "Constants.h"

Weapon::Weapon()
	: m_name{}
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

	gLaserSound.playChunk(-1, 0, 100);
}

void Weapon::updatePlayerProjectiles()
{
	if (!m_projectiles.empty())
	{
		for (int i = 0; i < m_projectiles.size(); ++i)
		{
			m_projectiles[i].updateCollider();

			if (m_projectiles[i].getPosY() < 0 - gProjectileTexture.getHeight() || m_projectiles[i].checkCollision(gWave.getEnemies()))
			{
				m_projectiles.erase(m_projectiles.begin() + i);

				break;
			}
			else
			{
				gProjectileTexture.render(m_projectiles[i].getPosX(), m_projectiles[i].getPosY(), &gRedLaserClip, gRedLaserClip.w, gRedLaserClip.h, 90);

				#if defined(_DEBUG)
				// Projectile Debug Info
				m_projectiles[i].debug();
				#endif

				m_projectiles[i].move(LASER_VEL);
			}

		}
	}
}

void Weapon::updateEnemyProjectiles()
{
	if (!m_projectiles.empty())
	{
		for (int i = 0; i < m_projectiles.size(); ++i)
		{
			m_projectiles[i].updateCollider();

			if (m_projectiles[i].getPosY() > SCREEN_HEIGHT || m_projectiles[i].checkCollision(gPlayer))
			{
				m_projectiles.erase(m_projectiles.begin() + i);

				break;
			}
			else
			{
				gProjectileTexture.render(m_projectiles[i].getPosX(), m_projectiles[i].getPosY(), &gRedLaserClip, gRedLaserClip.w, gRedLaserClip.h, 90);

				#if defined(_DEBUG)
				// Projectile Debug Info
				m_projectiles[i].debug();
				#endif

				m_projectiles[i].move(-LASER_VEL);
			}
		}
	}
}

std::string& Weapon::getName()
{
	return m_name;
}

int Weapon::getDamage() const
{
	return m_damage;
}