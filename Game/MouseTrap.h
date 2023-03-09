#pragma once
#include "GameArea.h"

class IMouseTrapState;
class IdleState;
class SetState;

class MouseTrap : public GameAreaObject
{

public:
	MouseTrap();
	~MouseTrap();

	void OnCurrentSquare(void* pObj) override;

	virtual void Update() override;

	friend class SetState;
	friend class IdleState;

private:
	IMouseTrapState* pState;
	IdleState* m_idleState;
	SetState* m_setState;

	bool m_tripped;
};

