#include "Particle.h"

Particle::Particle()
	: m_sprite{}
	, m_clips{}
{
}

Particle::~Particle()
{
	m_sprite.free();
}