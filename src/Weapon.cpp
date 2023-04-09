#include "Weapon.h"
#include "Globals.h"
#include "Constants.h"

Weapon::Weapon()
	: m_name{}
	, m_damage{}
	, m_projectiles{}
	, m_debugIndex{}
{
}

Weapon::~Weapon()
{
	for (auto& projectile : m_projectiles)
	{
		projectile.first.getTexture().free();
		projectile.second.getTexture().free();
	}
}

void Weapon::shoot()
{
	Projectile leftCannon{};
	leftCannon.setPosX(gPlayer.getPosX() + 31);
	leftCannon.setPosY(gPlayer.getPosY());

	Projectile rightCannon{};
	rightCannon.setPosX(gPlayer.getPosX() + 61);
	rightCannon.setPosY(gPlayer.getPosY() + 1);

	std::pair<Projectile, Projectile> p{ leftCannon, rightCannon };
	m_projectiles.push_back(p);

	 // Left Cannon Debug Info
	printf("Left Cannon Pos X: %d\n", m_projectiles.at(m_debugIndex).first.getPosX());
	printf("Left Cannon Pos Y: %d\n", m_projectiles.at(m_debugIndex).first.getPosY());
	printf("Left Cannon Width: %d\n", m_projectiles.at(m_debugIndex).first.getTexture().getWidth());
	printf("Left Cannon Height: %d\n\n", m_projectiles.at(m_debugIndex).first.getTexture().getHeight());

	// Right Cannon Debug Info
	printf("Right Cannon Pos X: %d\n", m_projectiles.at(m_debugIndex).second.getPosX());
	printf("Right Cannon Pos Y: %d\n", m_projectiles.at(m_debugIndex).second.getPosY());
	printf("Right Cannon Width: %d\n", m_projectiles.at(m_debugIndex).second.getTexture().getWidth());
	printf("Right Cannon Height: %d\n\n", m_projectiles.at(m_debugIndex).second.getTexture().getHeight());
	++m_debugIndex;
}

void Weapon::updateProjectiles()
{
	int i = 0;

	for (auto& projectilePair : m_projectiles)
	{
		if (m_projectiles.at(i).first.getPosY() < 0 - gProjectileTexture.getHeight())
		{
			m_projectiles.erase(m_projectiles.begin() + i);
			--i;
			--m_debugIndex;
		}
		else
		{
			gProjectileTexture.render(projectilePair.first.getPosX(), projectilePair.first.getPosY(), &gRedLaserClip, gRedLaserClip.w, gRedLaserClip.h, 90);
			gProjectileTexture.render(projectilePair.second.getPosX(), projectilePair.second.getPosY(), &gRedLaserClip, gRedLaserClip.w, gRedLaserClip.h, -90);

			// Left Cannon Debug Info
			printf("Left Cannon Pos X: %d\n", projectilePair.first.getPosX());
			printf("Left Cannon Pos Y: %d\n", projectilePair.first.getPosY());

			// Right Cannon Debug Info
			printf("Right Cannon Pos X: %d\n", projectilePair.second.getPosX());
			printf("Right Cannon Pos Y: %d\n\n", projectilePair.second.getPosY());

			projectilePair.first.move();
			projectilePair.second.move();
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