#pragma once

class IApplicationState;
class IGameState;

class Time
{
public:
	static float GetAppStateTime();
	static float GetOverallTime();
	static float GetGameStateTime();
	static float GetElapsedTime();

	friend class ApplicationManager;	//	So these classes can reset 
	friend class GameManager;			//	the member variables to zero
private:
	static inline IApplicationState* m_pCurrentAppState;
	static inline IGameState* m_pCurrentGameState;
	static inline float m_overallTime{ 0.f };
	static inline float m_elapsedTime{ 0.f };
};
