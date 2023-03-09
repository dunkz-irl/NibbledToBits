#include "Play.h"

#include "MouseTrapStates.h"
#include "MouseTrap.h"
#include "Time.h"

void IdleState::OnEnter(MouseTrap* pTrap)
{
	pTrap->id = GameAreaObjects::TRAP_01_SET;
}


IMouseTrapState* IdleState::OnUpdate(MouseTrap* pTrap)
{
	// throw std::logic_error("The method or operation is not implemented.");
	if (pTrap->m_tripped)
	{
		return pTrap->m_setState;
	}
	else
	{
		return nullptr;
	}
}

void IdleState::OnExit(MouseTrap* pTrap)
{
	// throw std::logic_error("The method or operation is not implemented.");
}

void SetState::OnEnter(MouseTrap* pTrap)
{
	pTrap->id = GameAreaObjects::TRAP_01_NOTSET;
}

IMouseTrapState* SetState::OnUpdate(MouseTrap* pTrap)
{
	m_timer += Time::GetElapsedTime();

	if (m_timer > m_resetTime)
	{
		m_timer = 0.f;
		return pTrap->m_idleState;
	}
	else
	{
		return nullptr;
	}
}

void SetState::OnExit(MouseTrap* pTrap)
{
	pTrap->m_tripped = false;
	// throw std::logic_error("The method or operation is not implemented.");
}
