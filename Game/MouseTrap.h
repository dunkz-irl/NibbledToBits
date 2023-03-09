#pragma once
#include "GameArea.h"

class IMouseTrapState;
class SetState;
class TrippedState;

class MouseTrap : public GameAreaObject
{

public:
	MouseTrap();
	~MouseTrap();

	void OnCurrentSquare(void* pObj) override;

	virtual void Update() override;

	friend class TrippedState;
	friend class SetState;

private:
	IMouseTrapState* pState;
	SetState* m_idleState;
	TrippedState* m_setState;

	bool m_tripped;
};

