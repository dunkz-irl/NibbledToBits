#pragma once
class IGameState
{
public:
	~IGameState() = default;
	virtual void OnEnter() = 0;
	virtual void OnExit() = 0;
	virtual IGameState* OnUpdate() = 0;
	virtual void OnDraw() = 0;
};