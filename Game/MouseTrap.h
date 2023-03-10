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
	void Update() override;
	void Reset() override;

	friend class TrippedState;
	friend class SetState;

private:
	IMouseTrapState* pState;
	SetState* m_setState;
	TrippedState* m_trippedState;

	bool m_tripped{ false };
};

