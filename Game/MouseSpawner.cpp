#include "MouseSpawner.h"
#include "Time.h"

bool MouseSpawner::Update()
{
	// Spawn immediately if this is the first mouse to prevent a delay
	if (m_spawnedMice == 0)
	{
		m_spawnTimer = 0.f;
		m_spawnedMice++;
		return true;
	}

	m_spawnTimer += Time::GetElapsedTime();

	if (m_spawnTimer > 1.f / m_spawnRate)
	{
		if (m_spawnedMice < m_numMice)
		{
			m_spawnTimer = 0.f;
			m_spawnedMice++;
			return true;
		}
	}
	return false;
}
