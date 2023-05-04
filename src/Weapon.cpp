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

	Projectile leftCannon{};
	leftCannon.setPos(leftCannonPos);
	leftCannon.setType(LEFT_PROJECTILE);
	leftCannon.setCollider(gLeftLaserHitBox);

	m_projectiles.push_back(leftCannon);

	Projectile rightCannon{};
	rightCannon.setPos(rightCannonPos);
	rightCannon.setType(RIGHT_PROJECTILE);
	rightCannon.setCollider(gRightLaserHitBox);

	m_projectiles.push_back(rightCannon);

	gLaserSound.playChunk(-1, 0, 100);
}

void Weapon::updatePlayerProjectiles()
{
	// Cannon
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
				// Cannon Debug Info
				m_projectiles[i].debug();
				#endif

				m_projectiles[i].move(LASER_VEL);
			}

		}
	}
}

void Weapon::updateEnemyProjectiles()
{
	// Cannon
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
				// Cannon Debug Info
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