#include "Weapon.h"
#include "Common.h"

Weapon::Weapon(EntityType ownerType, Vector2<float> weaponDirection)
	: m_ownerType{ ownerType }
	, m_name{}
	, m_damage{}
	, m_projectiles{}
	, m_weaponDirection{ weaponDirection }
{
}

void Weapon::shoot(Pair<int> leftCannonPos, Pair<int> rightCannonPos)
{
	Projectile leftProjectile{};
	leftProjectile.setPos(leftCannonPos);
	leftProjectile.setDirection(m_weaponDirection);
	leftProjectile.setType(LEFT_PROJECTILE);
	leftProjectile.createCollider();
	leftProjectile.updateCollider();

	m_projectiles.push_back(leftProjectile);

	Projectile rightProjectile{};
	rightProjectile.setPos(rightCannonPos);
	rightProjectile.setDirection(m_weaponDirection);
	rightProjectile.setType(RIGHT_PROJECTILE);
	rightProjectile.createCollider();
	rightProjectile.updateCollider();

	m_projectiles.push_back(rightProjectile);

	resourceManager.getSoundSystem().findSound("sfx_laser")->playChunk(-1, 0, 50);
}

void Weapon::updateProjectiles(double dt)
{
	if (!m_projectiles.empty())
	{
		for (int i = 0; i < m_projectiles.size(); ++i)
		{
			if (m_projectiles[i].checkScreenBoundary() || m_projectiles[i].checkCollision(gEnts, m_ownerType))
			{
				m_projectiles.erase(m_projectiles.begin() + i);
				break;
			}
			else
			{
				m_projectiles[i].move(dt);
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
			m_projectiles[i].render();
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