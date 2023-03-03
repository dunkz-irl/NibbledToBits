#pragma once

class IGameState;

class Time
{
public:
	static float GetStateTime();
private:
	static inline IGameState* m_pCurrentState;
};
