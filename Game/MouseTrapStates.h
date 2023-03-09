#pragma once
#include "GameAreaObjects.h"

class MouseTrap;

class IMouseTrapState
{
public:
	virtual IMouseTrapState* OnUpdate(MouseTrap*) = 0;
	virtual void OnEnter(MouseTrap* pTrap) = 0;
	virtual void OnExit(MouseTrap* pTrap) = 0;
};

class IdleState : public IMouseTrapState
{
public:
	virtual void OnEnter(MouseTrap* pTrap) override;
	virtual IMouseTrapState* OnUpdate(MouseTrap*) override;
	virtual void OnExit(MouseTrap* pTrap) override;

};

class SetState : public IMouseTrapState
{
public:
	virtual void OnEnter(MouseTrap* pTrap) override;
	virtual IMouseTrapState* OnUpdate(MouseTrap*) override;
	virtual void OnExit(MouseTrap* pTrap) override;

private:
	float m_timer{ 0.f };
	float m_resetTime{ 2.f };
};