#pragma once

// #CreateEmitter
enum class EmitterType
{
	SMOKE = 0,
	PORTAL,
	SMOKEPUFF,
	SMOKEPUFFSMALL,
	CHEESE,
	CONFETTI,
	WINTEXT
};

class Emitter;

class ParticleManager
{
public:
	void UpdateEmitters(float elapsedTime);
	int CreateEmitter(EmitterType emitter, Play::Point2f pos, float lifetime, float scale = 1.f);
	void DrawParticles();
	void DestroyEmitter(std::vector<Emitter*>::iterator& it);

	Emitter& GetEmitter(int id);

	// Singleton
	static ParticleManager& Instance(int maxEmitters); // For initialisation
	static ParticleManager& Instance(); // General access
	static void Destroy();

private:
	// Singleton
	ParticleManager();  // Private constructor and destructor
	~ParticleManager();
	static ParticleManager* s_pInstance; // Wha' th' !&*%?&* is thi'? // It's a staic pointer to the instance

	ParticleManager& operator=(const ParticleManager&) = delete; // No assignment allowed
	ParticleManager(const ParticleManager&) = delete; // No copy constructor allowed;

	std::vector<Emitter*> m_v_pEmitters{};
	int m_maxEmitters{ 100 };
};