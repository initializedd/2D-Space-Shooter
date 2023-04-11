#include "Entity.h"

Entity::Entity()
	: m_texture{}
	, m_width{}
	, m_height{}
	, m_pos{}
	, m_vel{}
	, m_health{}
	, m_particle{}
	, m_weapon{}
{
	m_colliders.resize(11);

	m_colliders[0].w = 6;
	m_colliders[0].h = 1;

	m_colliders[1].w = 10;
	m_colliders[1].h = 1;

	m_colliders[2].w = 14;
	m_colliders[2].h = 1;

	m_colliders[3].w = 16;
	m_colliders[3].h = 2;

	m_colliders[4].w = 18;
	m_colliders[4].h = 2;

	m_colliders[5].w = 20;
	m_colliders[5].h = 6;

	m_colliders[6].w = 18;
	m_colliders[6].h = 2;

	m_colliders[7].w = 16;
	m_colliders[7].h = 2;

	m_colliders[8].w = 14;
	m_colliders[8].h = 1;

	m_colliders[9].w = 10;
	m_colliders[9].h = 1;

	m_colliders[10].w = 6;
	m_colliders[10].h = 1;

	shiftColliders();
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

bool Entity::checkCollision(std::vector<SDL_Rect>& a, std::vector<SDL_Rect>& b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Go through the A boxes
	for (int Abox = 0; Abox < a.size(); Abox++)
	{
		//Calculate the sides of rect A
		leftA = a[Abox].x;
		rightA = a[Abox].x + a[Abox].w;
		topA = a[Abox].y;
		bottomA = a[Abox].y + a[Abox].h;

		//Go through the B boxes
		for (int Bbox = 0; Bbox < b.size(); Bbox++)
		{
			//Calculate the sides of rect B
			leftB = b[Bbox].x;
			rightB = b[Bbox].x + b[Bbox].w;
			topB = b[Bbox].y;
			bottomB = b[Bbox].y + b[Bbox].h;

			//If no sides from A are outside of B
			if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false)
			{
				//A collision is detected
				return true;
			}
		}
	}

	//If neither set of collision boxes touched
	return false;
}

void Entity::shiftColliders()
{
	//The row offset
	int r = 0;

	//Go through the dot's collision boxes
	for (int set = 0; set < m_colliders.size(); ++set)
	{
		//Center the collision box
		m_colliders[set].x = m_pos.x + (getTexture().getWidth() - m_colliders[set].w) / 2;

		//Set the collision box at its row offset
		m_colliders[set].y = m_pos.y + r;

		//Move the row offset down the height of the collision box
		r += m_colliders[set].h;
	}
}

std::vector<SDL_Rect>& Entity::getColliders()
{
	return m_colliders;
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