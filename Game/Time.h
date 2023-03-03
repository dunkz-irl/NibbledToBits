#pragma once

class IGameState;

class Time
{
public:
	static float GetStateTime();
	static float GetOverallTime();

	friend class ApplicationManager;
private:
	static inline IGameState* m_pCurrentState;
	static inline float m_overallTime{ 0.f };
};
