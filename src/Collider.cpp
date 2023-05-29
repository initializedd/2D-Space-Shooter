#include "Collider.h"
#include "Constants.h"

Collider::Collider()
	: m_rect{}
	, m_offset{}
{
}

Collider::Collider(SDL_Rect& rect)
	: m_rect{ rect }
	, m_offset{ rect.x, rect.y }
{
}

bool Collider::intersects(const Collider& collider)
{
	return SDL_HasIntersection(&m_rect, &collider.m_rect);
}

void Collider::handleCollision(Vector2<float>& pos, const Vector2<float>& otherPos, Collider& otherCollider, double rotation)
{
	setColliders(pos, rotation);

	if (pos.x <= otherPos.x)
		pos.x = (otherPos.x - (otherPos.x - otherCollider.getRect().x)) - ((m_rect.x - pos.x) + m_rect.w);

	if (pos.x > otherPos.x)
		pos.x = (otherCollider.getRect().x + otherCollider.getRect().w) - (m_rect.x - pos.x);

	if (pos.y <= otherPos.y)
		pos.y = (otherPos.y - (otherPos.y - otherCollider.getRect().y)) - ((m_rect.y - pos.y) + m_rect.h);

	if (pos.y > otherPos.y)
		pos.y = (otherCollider.getRect().y + otherCollider.getRect().h) - (m_rect.y - pos.y);

	setColliders(pos, rotation);
}

bool Collider::handleScreenCollision(Vector2<float>& pos, double rotation)
{
	setColliders(pos, rotation);

	bool handledCollision = false;

	// Check if outside of left screen boundary
	if (m_rect.x < 0.f)
	{
		pos.x += std::abs(m_rect.x);

		setColliders(pos, rotation);
		handledCollision = true;
	}

	// Check if outside of right screen boundary
	if (m_rect.x + m_rect.w > SCREEN_WIDTH)
	{
		float difference = std::abs(m_rect.x - pos.x);
		pos.x = SCREEN_WIDTH - m_rect.w - difference;

		setColliders(pos, rotation);
		handledCollision = true;
	}

	// Check if outside of top screen boundary
	if (m_rect.y < 0.f)
	{
		pos.y += std::abs(m_rect.y);

		setColliders(pos, rotation);
		handledCollision = true;
	}

	// Check if outside of bottom screen boundary
	if (m_rect.y + m_rect.h > SCREEN_HEIGHT)
	{
		float difference = std::abs(m_rect.y - pos.y);
		pos.y = SCREEN_HEIGHT - m_rect.h - difference;

		setColliders(pos, rotation);
		handledCollision = true;
	}

	return handledCollision;
}

SDL_Rect& Collider::getRect()
{
	return m_rect;
}

void Collider::setColliders(Vector2<float>& pos, double rotation)
{
	double textureRadians = rotation * (M_PI / 180.0);

	// Calculate the cosine and sine values of the texture's rotation angle
	double cosAngle = cos(textureRadians);
	double sinAngle = sin(textureRadians);

	// Calculate the centre coordinates of the rotated texture
	//double textureCentreX = m_ship.getTexture().getWidth() / 2.0;
	double textureCentreX = 64.0 / 2.0;
	//double textureCentreY = m_ship.getTexture().getHeight() / 2.0;
	double textureCentreY = 80.0 / 2.0;

	// Calculate the centre coordinates of the collider
	double colliderCentreX = m_rect.w / 2.0;
	double colliderCentreY = m_rect.h / 2.0;

	// Translate the collider's centre to the texture's coordinate system
	double translatedX = m_offset.x + colliderCentreX - textureCentreX;
	double translatedY = m_offset.y + colliderCentreY - textureCentreY;

	// Rotate the collider's positions relative to the texture's rotation
	double rotatedX = translatedX * cosAngle - translatedY * sinAngle;
	double rotatedY = translatedX * sinAngle + translatedY * cosAngle;

	// Translate the rotated collider's positions back to the original coordinate system
	m_rect.x = static_cast<int>(rotatedX + textureCentreX - colliderCentreX + pos.x);
	m_rect.y = static_cast<int>(rotatedY + textureCentreY - colliderCentreY + pos.y);
}