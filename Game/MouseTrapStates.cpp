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
		return pTrap->m_setState;
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
	float scale = 2.f - EaseOutElastic(m_timer * 1.1f / m_resetTime);

	// Animation
	pTrap->m_matrix = MatrixScale(scale, scale); // #TODO: Couldn't get translation working
	pTrap->m_matrix = pTrap->m_matrix * MatrixRotation(sin((pow(m_resetTime * 2.f - m_timer * 2.f, 3.f))/-1.f) / 3.f);
	//pTrap->m_matrix.row[2] = GameArea::GameToWorld({ pTrap->posx, pTrap->posy }) + Play::Point2f{ 0.f, scale * 100.f };

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

void TrippedState::OnExit(MouseTrap* pTrap)
{
	pTrap->m_tripped = false;
}
