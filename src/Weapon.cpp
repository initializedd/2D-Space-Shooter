#include "Weapon.h"
#include "Globals.h"
#include "Constants.h"

Weapon::Weapon()
	: m_name{}
	, m_damage{}
	, m_projectiles{}
	, m_debugIndex{}
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

	Projectile rightCannon{};
	rightCannon.setPosX(gPlayer.getPosX() + 61);
	rightCannon.setPosY(gPlayer.getPosY() + 1);

	Pair projectilePair{ leftCannon, rightCannon };
	m_projectiles.push_back(projectilePair);

	 // Left Cannon Debug Info
	printf("Left Cannon Pos X: %d\n", m_projectiles.at(m_debugIndex).x.getPosX());
	printf("Left Cannon Pos Y: %d\n", m_projectiles.at(m_debugIndex).x.getPosY());
	printf("Left Cannon Width: %d\n", m_projectiles.at(m_debugIndex).x.getTexture().getWidth());
	printf("Left Cannon Height: %d\n\n", m_projectiles.at(m_debugIndex).x.getTexture().getHeight());

	// Right Cannon Debug Info
	printf("Right Cannon Pos X: %d\n", m_projectiles.at(m_debugIndex).y.getPosX());
	printf("Right Cannon Pos Y: %d\n", m_projectiles.at(m_debugIndex).y.getPosY());
	printf("Right Cannon Width: %d\n", m_projectiles.at(m_debugIndex).y.getTexture().getWidth());
	printf("Right Cannon Height: %d\n\n", m_projectiles.at(m_debugIndex).y.getTexture().getHeight());
	++m_debugIndex;
	
	gLaserSound.playChunk(-1, 0);
}

void Weapon::updateProjectiles()
{
	int i = 0;

	for (auto& projectilePair : m_projectiles)
	{
		if (m_projectiles.at(i).x.getPosY() < 0 - gProjectileTexture.getHeight())
		{
			m_projectiles.erase(m_projectiles.begin() + i);
			--i;
			--m_debugIndex;
		}
		else
		{
			gProjectileTexture.render(projectilePair.x.getPosX(), projectilePair.x.getPosY(), &gRedLaserClip, gRedLaserClip.w, gRedLaserClip.h, 90);
			gProjectileTexture.render(projectilePair.y.getPosX(), projectilePair.y.getPosY(), &gRedLaserClip, gRedLaserClip.w, gRedLaserClip.h, -90);

			// Left Cannon Debug Info
			printf("Left Cannon Pos X: %d\n", projectilePair.x.getPosX());
			printf("Left Cannon Pos Y: %d\n", projectilePair.x.getPosY());

			// Right Cannon Debug Info
			printf("Right Cannon Pos X: %d\n", projectilePair.y.getPosX());
			printf("Right Cannon Pos Y: %d\n\n", projectilePair.y.getPosY());

			projectilePair.x.move();
			projectilePair.y.move();
		}

		++i;
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