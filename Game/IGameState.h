#pragma once
class IGameState
{
public:
	~IGameState() = default;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual IGameState* OnUpdate() = 0;
	virtual void OnDraw() = 0;

	static float GetStateTime() { return m_stateTime; };

	friend class ApplicationManager;

protected:
	static inline float m_stateTime{ 0.f }; // #TODO: I have no idea what inline means, but it lets this be static
};