#include "Weapon.h"
#include "Globals.h"
#include "Constants.h"

Weapon::Weapon()
	: m_name{}
	, m_damage{}
	, m_leftProjectiles{}
	, m_rightProjectiles{}
	, m_leftDebugIndex{}
	, m_rightDebugIndex{}
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
	leftCannon.setPosX(leftCannonPos.x);
	leftCannon.setPosY(leftCannonPos.y);
	leftCannon.setCollider(gLeftLaserHitBox);

	m_leftProjectiles.push_back(leftCannon);

	#if defined(_DEBUG)
	// Left Cannon Debug Info
	//leftCannon.debug(LEFT_PROJECTILE);
	++m_leftDebugIndex;
	#endif

	Projectile rightCannon{};
	rightCannon.setPosX(rightCannonPos.x);
	rightCannon.setPosY(rightCannonPos.y);
	rightCannon.setCollider(gRightLaserHitBox);

	m_rightProjectiles.push_back(rightCannon);

	#if defined(_DEBUG)
	// Right Cannon Debug Info
	//rightCannon.debug(RIGHT_PROJECTILE);
	++m_rightDebugIndex;
	#endif

	gLaserSound.playChunk(-1, 0, 100);
}

void Weapon::updatePlayerProjectiles()
{
	// Left Cannon
	if (!m_leftProjectiles.empty())
	{
		for (int i = 0; i < m_leftProjectiles.size(); ++i)
		{
			m_leftProjectiles[i].setCollider(gLeftLaserHitBox);

			if (m_leftProjectiles[i].getPosY() < 0 - gProjectileTexture.getHeight() || m_leftProjectiles[i].checkCollision(gWave.getEnemies()))
			{
				m_leftProjectiles.erase(m_leftProjectiles.begin() + i);

				#if defined(_DEBUG)
				printf("Left Cannon Destroyed!\n");
				--m_leftDebugIndex;
				#endif

				break;
			}
			else
			{
				gProjectileTexture.render(m_leftProjectiles[i].getPosX(), m_leftProjectiles[i].getPosY(), &gRedLaserClip, gRedLaserClip.w, gRedLaserClip.h, 90);

				#if defined(_DEBUG)
				// Left Cannon Debug Info
				m_leftProjectiles[i].debug(LEFT_PROJECTILE);
				#endif

				m_leftProjectiles[i].move(LASER_VEL);
			}

		}
	}

	// Right Cannon
	if (!m_rightProjectiles.empty())
	{
		for (int i = 0; i < m_rightProjectiles.size(); ++i)
		{
			m_rightProjectiles[i].setCollider(gRightLaserHitBox);

			if (m_rightProjectiles[i].getPosY() < 0 - gProjectileTexture.getHeight() || m_rightProjectiles[i].checkCollision(gWave.getEnemies()))
			{
				m_rightProjectiles.erase(m_rightProjectiles.begin() + i);

				#if defined(_DEBUG)
				printf("Right Cannon Destroyed!\n");
				--m_rightDebugIndex;
				#endif

				break;
			}
			else
			{
				gProjectileTexture.render(m_rightProjectiles[i].getPosX(), m_rightProjectiles[i].getPosY(), &gRedLaserClip, gRedLaserClip.w, gRedLaserClip.h, -90);

				#if defined(_DEBUG)
				// Right Cannon Debug Info
				m_rightProjectiles[i].debug(RIGHT_PROJECTILE);
				#endif

				m_rightProjectiles[i].move(LASER_VEL);
			}
		}
	}
}

void Weapon::updateEnemyProjectiles()
{
	// Left Cannon
	if (!m_leftProjectiles.empty())
	{
		for (int i = 0; i < m_leftProjectiles.size(); ++i)
		{
			m_leftProjectiles[i].setCollider(gLeftLaserHitBox);

			if (m_leftProjectiles[i].getPosY() > SCREEN_HEIGHT || m_leftProjectiles[i].checkCollision(gPlayer))
			{
				m_leftProjectiles.erase(m_leftProjectiles.begin() + i);

				#if defined(_DEBUG)
				printf("Left Cannon Destroyed!\n");
				--m_leftDebugIndex;
				#endif

				break;
			}
			else
			{
				gProjectileTexture.render(m_leftProjectiles[i].getPosX(), m_leftProjectiles[i].getPosY(), &gRedLaserClip, gRedLaserClip.w, gRedLaserClip.h, 90);

				#if defined(_DEBUG)
				// Left Cannon Debug Info
				m_leftProjectiles[i].debug(LEFT_PROJECTILE);
				#endif

				m_leftProjectiles[i].move(-LASER_VEL);
			}
		}
	}

	// Right Cannon
	if (!m_rightProjectiles.empty())
	{
		for (int i = 0; i < m_rightProjectiles.size(); ++i)
		{
			m_rightProjectiles[i].setCollider(gRightLaserHitBox);

			if (m_rightProjectiles[i].getPosY() > SCREEN_HEIGHT || m_rightProjectiles[i].checkCollision(gPlayer))
			{
				m_rightProjectiles.erase(m_rightProjectiles.begin() + i);

				#if defined(_DEBUG)
				printf("Right Cannon Destroyed!\n");
				--m_rightDebugIndex;
				#endif

				break;
			}
			else
			{
				gProjectileTexture.render(m_rightProjectiles[i].getPosX(), m_rightProjectiles[i].getPosY(), &gRedLaserClip, gRedLaserClip.w, gRedLaserClip.h, -90);

				#if defined(_DEBUG)
				// Right Cannon Debug Info
				m_rightProjectiles[i].debug(RIGHT_PROJECTILE);
				#endif

				m_rightProjectiles[i].move(-LASER_VEL);
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