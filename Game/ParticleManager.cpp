#include "Play.h"
#include "Particle.h"
#include "Emitter.h"
#include "PolygonEmitter.h"
#include "EmitterTypes.h"
#include "ParticleManager.h"
#include "Common.h"

ParticleManager* ParticleManager::s_pInstance = nullptr;

const Play::Vector2f PARTICLE_GRAVITY{ 0.f, 0.5f };

#pragma warning(disable: 4715) // Asserts placed where values are not returned

// +~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-+ //
// |  Constructor & Destructor (private)  |	//
// +~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-+ //

ParticleManager::ParticleManager()
{
	s_pInstance = this;
}

ParticleManager::~ParticleManager()
{
	s_pInstance = nullptr;
	delete s_pInstance;
}

ParticleManager& ParticleManager::Instance(int maxEmitters)
{
	// Assert if s_pInstance is not nullptr
	PLAY_ASSERT_MSG(!s_pInstance, "Trying to create multiple instances of the ParticleManager singleton.");
	s_pInstance = new ParticleManager();
	s_pInstance->m_maxEmitters = maxEmitters;
	return *s_pInstance;
}

ParticleManager& ParticleManager::Instance()
{
	// Assert if s_pInstance is nullptr
	if (!s_pInstance)
	{
		s_pInstance = new ParticleManager();
	}

	PLAY_ASSERT_MSG(s_pInstance, "Trying to access ParticleManager without initialising it.");
	return *s_pInstance;
}

void ParticleManager::UpdateEmitters(float elapsedTime)
{
	for (Emitter* e : m_v_pEmitters)
	{
		e->Update(elapsedTime);
	}

	// Check for emitters whose lifetime has ended
	std::vector<Emitter*>::iterator it = m_v_pEmitters.begin();
	for (Emitter* e : m_v_pEmitters)
	{
		if (e->LifetimeEnded())
		{
			DestroyEmitter(it);
		}
		if (it != m_v_pEmitters.end())
		{
			it++;
		}
	}
}

void ParticleManager::DrawParticles()
{

	for (Emitter* e : m_v_pEmitters)
	{
		e->DrawParticles();
	}
}

int ParticleManager::CreateEmitter(EmitterType type, Play::Point2f pos, float lifetime, float scale)
{
	Emitter* pEmitter = nullptr;

	switch (type)
	{
	case EmitterType::SMOKE:
		pEmitter = new Smoke(pos, lifetime);
		break;
	case EmitterType::PORTAL:
		pEmitter = new Portal(pos, lifetime, scale);
		break;
	case EmitterType::SMOKEPUFF:
		pEmitter = new SmokePuff(pos, lifetime);
		break;
	case EmitterType::CHEESE:
		pEmitter = new CheeseConfetti(pos, lifetime);
		break;
	case EmitterType::CONFETTI:
		pEmitter = new Confetti(pos, lifetime);
		break;
	default:
		PLAY_ASSERT_MSG(false, "Invalid Emitter type (default case).");
		break;
	}

	if (pEmitter)
	{
		if (pEmitter->GetID() == -1)
		{
			PLAY_ASSERT_MSG(false, "Emitter has invalid ID.");
		}
		else
		{
			m_v_pEmitters.push_back(pEmitter);
			return pEmitter->GetID();
		}
	}
		
	else
		PLAY_ASSERT_MSG(false, "Emitter is nullptr.");
}

void ParticleManager::DestroyEmitter(std::vector<Emitter*>::iterator& it)
{
	Emitter* pEmitter = *it;
	it = m_v_pEmitters.erase(it);
	delete pEmitter;
	// pEmitter = nullptr;
}

void ParticleManager::Destroy()
{
	for (Emitter* e : ParticleManager::Instance().m_v_pEmitters)
	{
		delete e;
	}

	ParticleManager::Instance().m_v_pEmitters.clear();

	PLAY_ASSERT_MSG(s_pInstance, "Trying to destroy ParticleManager without initialising it.");
	delete s_pInstance;
	// s_pInstance = nullptr;
}

Emitter& ParticleManager::GetEmitter(int id)
{
	for (Emitter* e : m_v_pEmitters)
	{
		if (e->GetID() == id)
		{
			return *e;
		}
		else
		{
			PLAY_ASSERT_MSG(false, "Emitter ID not found.");
		}
	}
}
