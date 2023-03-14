#pragma once
#include "GameStateTypes.h"

class IGameState
{
public:
	~IGameState()
	{
		free(m_previousState);
		m_stateTime = 0.f;
	};
	virtual void OnEnter() = 0;
	virtual void OnExit();
	virtual IGameState* OnUpdate() = 0;
	virtual void OnDraw() = 0;

	static float GetStateTime() { return m_stateTime; };

	friend class GameManager;

	GAMESTATE_ENUM GetGameStateType() { return m_thisState; };

protected:
	std::string m_debugStateName{ "" };
	bool m_proceedToNextState{ false };
	GAMESTATE_ENUM m_thisState{ GAMESTATE_ENUM::COUNT };
private:
	virtual void DrawDebugInfo();
	static inline float m_stateTime{ 0.f };
	IGameState* m_previousState;
};
