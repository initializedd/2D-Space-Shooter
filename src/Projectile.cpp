#include "Projectile.h"
#include "Common.h"
#include <cstdio>

Projectile::Projectile()
	: m_pos{}
	, m_direction{}
	, m_movement{}
	, m_collider{}
	, m_texture{}
	, m_type{}
	, m_damage{}
{
	m_damage = 50;
}

void Projectile::move(double dt)
{
	m_movement.calculateVelocity(m_direction, PROJECTILE_SPEED * sf.y);
	m_movement.move(m_pos, dt);
}

bool Projectile::checkScreenBoundary()
{
	SDL_Rect screen(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// Checks if projectile is outside the screen
	if (!SDL_HasIntersection(&m_collider.getRect(), &screen))
	{
		return true;
	}

	return false;
}

bool Projectile::checkCollision(std::vector<std::unique_ptr<Entity>>& ents, EntityType ownerType)
{
	for (int i = 0; i < ents.size(); ++i)
	{
		if (ownerType == ents[i]->getType())
			continue;

		for (int j = 0; j < ents[i]->getShip().getParts().size(); ++j)
		{
			// Check for collision
			if (m_collider.intersects(ents[i]->getShip().getParts()[j].getCollider()))
			{
				if (!ents[i]->isDead())
				{
					ents[i]->reduceHealth(m_damage);

					if (ents[i]->isDead())
					{
						resourceManager.getSoundSystem().findSound("sfx_explosion")->playChunk(-1, 0, 50);
					}
				}

				return true;
			}
		}
	}

	return false;
}

void Projectile::createCollider()
{
	switch (m_type)
	{
		case LEFT_PROJECTILE:
			m_collider = { gLeftProjectileHitBox };
			break;

		case RIGHT_PROJECTILE:
			m_collider = { gRightProjectileHitBox };
			break;
	}
}

void Projectile::updateCollider()
{
	m_collider.createColliders(m_pos, 0.0);
}

void Projectile::render()
{
	std::shared_ptr<Texture> projectile = resourceManager.getTextureSystem().findTexture("tex_projectile");

	switch (m_type)
	{
		case LEFT_PROJECTILE:
			projectile->render(m_pos.x, m_pos.y, gRedProjectileClip.w, gRedProjectileClip.h, &gRedProjectileClip, 90);
			break;

		case RIGHT_PROJECTILE:
			projectile->render(m_pos.x, m_pos.y, gRedProjectileClip.w, gRedProjectileClip.h, &gRedProjectileClip, 90, nullptr, SDL_FLIP_VERTICAL);
			break;
	}

	#if defined(_DEBUG)
	// Projectile Debug Info
	debug();
	#endif
}

void Projectile::debug()
{
	const SDL_Rect& rect = m_collider.getRect();

	//std::stringstream pos;
	//pos.str(std::to_string(rect.x) + ',' + std::to_string(rect.y));

	const std::string posText = std::to_string(rect.x) + ',' + std::to_string(rect.y);

	std::shared_ptr<Text> projectileText = resourceManager.getTextSystem().findTextStream("txt_projectile");
	std::shared_ptr<Font> futura = resourceManager.getTextSystem().findFont("ttf_futura");

	if (!projectileText->loadFromText(posText, futura->getFont(), SDL_Color(0x00, 0xFF, 0x00, 0xFF)))
		return;

	switch (m_type)
	{
		case LEFT_PROJECTILE:
			if (m_movement.getVel().y < 0)
				projectileText->getTexture()->render(rect.x - projectileText->getTexture()->getWidth() - 1, rect.y - projectileText->getTexture()->getHeight(), projectileText->getTexture()->getWidth(), projectileText->getTexture()->getHeight(), nullptr);

			else if (m_movement.getVel().y > 0)
				projectileText->getTexture()->render(rect.x + rect.w, rect.y - projectileText->getTexture()->getHeight(), projectileText->getTexture()->getWidth(), projectileText->getTexture()->getHeight(), nullptr);
			break;

		case RIGHT_PROJECTILE:
			if (m_movement.getVel().y < 0)
				projectileText->getTexture()->render(rect.x + rect.w, rect.y - projectileText->getTexture()->getHeight(), projectileText->getTexture()->getWidth(), projectileText->getTexture()->getHeight(), nullptr);

			else if (m_movement.getVel().y > 0)
				projectileText->getTexture()->render(rect.x - projectileText->getTexture()->getWidth() - 1, rect.y - projectileText->getTexture()->getHeight(), projectileText->getTexture()->getWidth(), projectileText->getTexture()->getHeight(), nullptr);
			break;
	}

	m_collider.drawCollider();
}

Vector2<float> Projectile::getPos() const
{
	return m_pos;
}

Texture& Projectile::getTexture()
{
	return m_texture;
}

ProjectileType Projectile::getType()
{
	return m_type;
}

void Projectile::setPos(Pair<int> pos)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
}

void Projectile::setDirection(Vector2<float> direction)
{
	m_direction.x = direction.x;
	m_direction.y = direction.y;
}

void Projectile::setTexture(Texture& texture)
{
	m_texture = texture;
}

void Projectile::setType(ProjectileType type)
{
	m_type = type;
}