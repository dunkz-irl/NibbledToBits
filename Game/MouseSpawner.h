#pragma once
class MouseSpawner
{
public:
	MouseSpawner(int numMice, float spawnRate)
	{
		m_numMice = numMice;
		m_spawnRate = spawnRate;
	}
	bool Update();
private:
	int m_numMice{ 0 };
	int m_spawnedMice{ 0 };
	float m_spawnRate{ 0 };
	float m_spawnTimer{ 0.f };
};

