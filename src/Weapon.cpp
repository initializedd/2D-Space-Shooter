#include "Weapon.h"
#include "Globals.h"
#include "Constants.h"

#define DEBUG

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

void Weapon::shoot()
{
	if (!m_lastShot.isStarted())
	{
		m_lastShot.start();
	}
	else if (m_lastShot.getTicks() < 250)
	{
		return; // not enough time has passed
	}
	m_lastShot.start();

	Projectile leftCannon{};
	leftCannon.setPosX(gPlayer.getPosX() + 31);
	leftCannon.setPosY(gPlayer.getPosY());
	leftCannon.setCollider();

	m_leftProjectiles.push_back(leftCannon);

	#if defined(DEBUG)
	// Left Cannon Debug Info
	printf("Left Cannon Pos X: %d\n", m_leftProjectiles.at(m_leftDebugIndex).getPosX());
	printf("Left Cannon Pos Y: %d\n", m_leftProjectiles.at(m_leftDebugIndex).getPosY());
	printf("Left Cannon Width: %d\n", m_leftProjectiles.at(m_leftDebugIndex).getCollider().w);
	printf("Left Cannon Height: %d\n\n", m_leftProjectiles.at(m_leftDebugIndex).getCollider().h);
	++m_leftDebugIndex;
	#endif

	Projectile rightCannon{};
	rightCannon.setPosX(gPlayer.getPosX() + 61);
	rightCannon.setPosY(gPlayer.getPosY() + 1);
	rightCannon.setCollider();

	m_rightProjectiles.push_back(rightCannon);

	#if defined(DEBUG)
	// Right Cannon Debug Info
	printf("Right Cannon Pos X: %d\n", m_rightProjectiles.at(m_rightDebugIndex).getPosX());
	printf("Right Cannon Pos Y: %d\n", m_rightProjectiles.at(m_rightDebugIndex).getPosY());
	printf("Right Cannon Width: %d\n", m_rightProjectiles.at(m_rightDebugIndex).getCollider().w);
	printf("Right Cannon Height: %d\n\n", m_rightProjectiles.at(m_rightDebugIndex).getCollider().h);
	++m_rightDebugIndex;
	#endif

	gLaserSound.playChunk(-1, 0);
}

void Weapon::updateProjectiles()
{
	// Left Cannon
	if (!m_leftProjectiles.empty())
	{
		for (int i = 0; i < m_leftProjectiles.size(); ++i)
		{
			if (m_leftProjectiles[i].getPosY() < 0 - gProjectileTexture.getHeight() || m_leftProjectiles[i].checkCollision(gEnemy.getCollider()))
			{
				m_leftProjectiles.erase(m_leftProjectiles.begin() + i);

				#if defined(DEBUG)
				printf("Left Cannon Destroyed!\n");
				--m_leftDebugIndex;
				#endif
			}
			else
			{
				gProjectileTexture.render(m_leftProjectiles[i].getPosX(), m_leftProjectiles[i].getPosY(), &gRedLaserClip, gRedLaserClip.w, gRedLaserClip.h, 90);

				#if defined(DEBUG)
				// Left Cannon Debug Info
				printf("Left Cannon Pos X: %d\n", m_leftProjectiles[i].getPosX());
				printf("Left Cannon Pos Y: %d\n", m_leftProjectiles[i].getPosY());
				#endif

				m_leftProjectiles[i].move();
			}
		}
	}

	// Right Cannon
	if (!m_rightProjectiles.empty())
	{
		for (int i = 0; i < m_rightProjectiles.size(); ++i)
		{
			if (m_rightProjectiles[i].getPosY() < 0 - gProjectileTexture.getHeight() || m_rightProjectiles[i].checkCollision(gEnemy.getCollider()))
			{
				m_rightProjectiles.erase(m_rightProjectiles.begin() + i);

				#if defined(DEBUG)
				printf("Right Cannon Destroyed!\n");
				--m_rightDebugIndex;
				#endif
			}
			else
			{
				gProjectileTexture.render(m_rightProjectiles[i].getPosX(), m_rightProjectiles[i].getPosY(), &gRedLaserClip, gRedLaserClip.w, gRedLaserClip.h, -90);

				#if defined(DEBUG)
				// Right Cannon Debug Info
				printf("Right Cannon Pos X: %d\n", m_rightProjectiles[i].getPosX());
				printf("Right Cannon Pos Y: %d\n\n", m_rightProjectiles[i].getPosY());
				#endif

				m_rightProjectiles[i].move();
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