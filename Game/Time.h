#pragma once

class IApplicationState;

class Time
{
public:
	static float GetStateTime();
	static float GetOverallTime();

	friend class ApplicationManager;
private:
	static inline IApplicationState* m_pCurrentState;
	static inline float m_overallTime{ 0.f };
};
