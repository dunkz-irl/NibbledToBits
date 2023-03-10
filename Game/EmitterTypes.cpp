#include "Play.h"
#include "Particle.h"
#include "Emitter.h"
#include "PolygonEmitter.h"
#include "EmitterTypes.h"

Smoke::Smoke(Play::Point2f pos, float lifetime)
{
	m_shape = SMOKE;
	m_pos = pos;
	m_lifetime = lifetime;

	SetSpawnRate(50.f);
	SetParticleLifetime(1.3f, 2.4f);
	SetScale(0.5f, 0.6f, 0.2f, 0.0f);
	SetOpacity(1.0f, 0.0f);
	SetDirection(0.f, 90.f, 0.f, 0.1f);
	SetGravity(true, UP, 0.25f);
	SetVelocity(1.1f, 5.2f);
	SetRotation(-0.1f, 0.1f, 0.0f, false);
	SetColour(Play::cGrey, 0.f, 10.f);
}

Portal::Portal(Play::Point2f pos, float lifetime, float scale)
{
	m_deleteOutOfBoundsParticles = true;
	m_pos = pos;
	m_shape = LINE;
	m_lifetime = lifetime;
	m_v_corners =
	{
		{0.f, 1.f},
		{0.5f, 0.f},
		{0.f, -1.f},
		{-0.5f, 0.f}
	};

	for (Play::Point2f& c : m_v_corners)
	{
		c *= scale;
	}

	SetSpawnRate(1000.f);
	SetRotation(0.0f, 0.0f, 0.f, true);
	SetVelocity(1.f, 6.f);
	SetScale(0.4f, 0.5f, -0.07f, 0.f);
	SetColour({ 50.f, 20.f, 5.f }, 10.f, 10.f);
	SetDirection(0.f, 0.f, 0.f, .25f);
	SetParticleLifetime(1.f, 2.f);
}