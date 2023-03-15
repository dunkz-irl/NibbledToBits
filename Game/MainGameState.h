#pragma once
#include "IApplicationState.h"

class MainGameState : public IApplicationState
{
public:
	void OnEnter();
	void OnExit();

	IApplicationState* OnUpdate();
	void OnDraw();

	friend class WinState;

private:
	static inline bool m_epilogue;
};
