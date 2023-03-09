#include "Play.h"

#include "Common.h"

#include "MouseTrapStates.h"
#include "MouseTrap.h"

#include "Mouse.h"

MouseTrap::MouseTrap()
{
	m_idleState = new IdleState();
	m_setState = new SetState();

	pState = m_idleState;
}

MouseTrap::~MouseTrap()
{
	delete m_idleState;
	delete m_setState;
}

void MouseTrap::OnCurrentSquare(void* pObj)
{
	Mouse* pMouse = static_cast<Mouse*>(pObj);

	if (!m_tripped)
	{
		m_tripped = true;
		pMouse->Thwart();
	}

	// #TODO: Some particle effect, puff of smoke maybe
}

void MouseTrap::Update()
{
	IMouseTrapState* pNewState = pState->OnUpdate(this);

	if (pNewState)
	{
		pState->OnExit(this);
		pState = pNewState;
		pState->OnEnter(this);
	}
}