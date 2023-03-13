#include "Play.h"

#include "MouseTrapStates.h"
#include "MouseTrap.h"
#include "Time.h"
#include "EasingFunctions.h"

void SetState::OnEnter(MouseTrap* pTrap)
{
	pTrap->id = GameAreaObjects::TRAP_01_SET;
}

IMouseTrapState* SetState::OnUpdate(MouseTrap* pTrap)
{
	// throw std::logic_error("The method or operation is not implemented.");
	if (pTrap->m_tripped)
	{
		return pTrap->m_trippedState;
	}
	else
	{
		return nullptr;
	}
}

void SetState::OnExit(MouseTrap* pTrap)
{
	// throw std::logic_error("The method or operation is not implemented.");
}

void TrippedState::OnEnter(MouseTrap* pTrap)
{
	pTrap->id = GameAreaObjects::TRAP_01_NOTSET;
}

IMouseTrapState* TrippedState::OnUpdate(MouseTrap* pTrap)
{
	m_timer += Time::GetElapsedTime();
	float scale = EastOutBounce(2.f, 1.f, m_timer * 1.5f);
	if (scale < 1.f) { scale = 1.f; };

	// Animation
	pTrap->m_matrix = MatrixScale(scale, scale);
	pTrap->m_matrix = pTrap->m_matrix * MatrixRotation(sin((pow(m_resetTime * 1.7f - m_timer * 1.7f, 3.f))/-1.f) / 3.f); // #TODO: Cool formula, should save into a function

	if (m_timer > m_resetTime)
	{
		m_timer = 0.f;
		return pTrap->m_setState;
	}
	else
	{
		return nullptr;
	}
}

void TrippedState::OnExit(MouseTrap* pTrap)
{
	m_timer = 0.f;
	pTrap->m_tripped = false;
}
