#include "Entity.h"

Entity::Entity(int x, int y)
	: m_texture{}
	, m_width{}
	, m_height{}
	, m_vel{}
	, m_health{}
	, m_particle{}
	, m_weapon{}
{
	m_pos.x = x;
	m_pos.y = y;
	
	//shiftColliders();
}

Entity::~Entity()
{
}

void Entity::move()
{

}

void Entity::shoot()
{
	m_weapon.shoot();
}

bool Entity::checkCollision(SDL_Rect& a, SDL_Rect& b)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	if (bottomA <= topB) { return false; }

	if (topA >= bottomB) { return false; }

	if (rightA <= leftB) { return false; }

	if (leftA >= rightB) { return false; }

	return true;
}

//void Entity::shiftColliders()
//{
//	//The row offset
//	int r = 0;
//
//	//Go through the dot's collision boxes
//	for (int set = 0; set < m_collider.size(); ++set)
//	{
//		//Center the collision box
//		m_collider[set].x = m_pos.x + (getTexture().getWidth() - m_collider[set].w) / 2;
//
//		//Set the collision box at its row offset
//		m_collider[set].y = m_pos.y + r;
//
//		//Move the row offset down the height of the collision box
//		r += m_collider[set].h;
//	}
//}

SDL_Rect& Entity::getCollider()
{
	return m_collider;
}


Texture& Entity::getTexture()
{
	return m_texture;
}

int Entity::getPosX() const
{
	return m_pos.x;
}

int Entity::getPosY() const
{
	return m_pos.y;
}

void Entity::setCollider()
{
	m_collider.x = m_pos.x;
	m_collider.y = m_pos.y;
	m_collider.w = m_pos.x + m_texture.getWidth();
	m_collider.h = m_pos.y + m_texture.getHeight();
}