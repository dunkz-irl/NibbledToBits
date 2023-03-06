#pragma once

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

protected:
	std::string m_debugStateName{ "" };
	bool m_proceedToNextState{ false };
private:
	virtual void DrawDebugInfo();
	static inline float m_stateTime{ 0.f };
	IGameState* m_previousState;
};
