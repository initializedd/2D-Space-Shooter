#include "Collider.h"
#include "../../Common/Common.h"
#include "../../Game/Game.h"
#include <cmath>

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

void Collider::handleCollision(Vector2<float>& pos, const Vector2<float>& otherPos, const Collider& otherCollider)
{
	float overlapX = std::min
	(
		m_rect.x + m_rect.w,
		otherCollider.getRect().x + otherCollider.getRect().w) - std::max(m_rect.x, otherCollider.getRect().x
	);

	float overlapY = std::min
	(
		m_rect.y + m_rect.h,
		otherCollider.getRect().y + otherCollider.getRect().h) - std::max(m_rect.y, otherCollider.getRect().y
	);

	if (overlapX < overlapY)
	{
		if (pos.x <= otherPos.x)
			pos.x += -overlapX;

		if (pos.x > otherPos.x)
			pos.x += overlapX;
	}
	else
	{
		if (pos.y <= otherPos.y)
			pos.y += -overlapY;

		if (pos.y > otherPos.y)
			pos.y += overlapY;
	}
}

bool Collider::handleScreenCollision(Vector2<float>& pos, double rotation)
{
	bool handledCollision = false;

	// Check if outside of left screen boundary
	if (m_rect.x < 0.f)
	{
		pos.x += std::abs(m_rect.x);

		handledCollision = true;
	}

	// Check if outside of right screen boundary
	if (m_rect.x + m_rect.w > SCREEN_WIDTH)
	{
		float difference = std::abs(m_rect.x - pos.x);
		pos.x = SCREEN_WIDTH - m_rect.w - difference;

		handledCollision = true;
	}

	// Check if outside of top screen boundary
	if (m_rect.y < 0.f)
	{
		pos.y += std::abs(m_rect.y);

		handledCollision = true;
	}

	// Check if outside of bottom screen boundary
	if (m_rect.y + m_rect.h > SCREEN_HEIGHT)
	{
		float difference = std::abs(m_rect.y - pos.y);
		pos.y = SCREEN_HEIGHT - m_rect.h - difference;

		handledCollision = true;
	}

	return handledCollision;
}

void Collider::drawCollider()
{
	SDL_SetRenderDrawColor(resourceManager.getRenderSystem().getWindow().getRenderer(), 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderDrawRect(resourceManager.getRenderSystem().getWindow().getRenderer(), &m_rect);
}

const SDL_Rect& Collider::getRect() const
{
	return m_rect;
}

void Collider::createColliders(Vector2<float>& pos, double rotation)
{
	double textureRadians = rotation * (M_PI / 180.0);

	// Calculate the cosine and sine values of the texture's rotation angle
	double cosAngle = cos(textureRadians);
	double sinAngle = sin(textureRadians);

	// Calculate the centre coordinates of the rotated texture
	//double textureCentreX = m_ship.getTexture().getWidth() / 2.0;
	double textureCentreX = (64.0 * sf.x) / 2.0;
	//double textureCentreY = m_ship.getTexture().getHeight() / 2.0;
	double textureCentreY = (80.0 * sf.y) / 2.0;

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