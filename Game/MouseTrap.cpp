#include "Play.h"

#include "Common.h"

#include "MouseTrapStates.h"
#include "MouseTrap.h"

#include "Mouse.h"
#include "ParticleManager.h"

MouseTrap::MouseTrap()
{
	m_setState = new SetState();
	m_trippedState = new TrippedState();

	pState = m_setState;
}

MouseTrap::~MouseTrap()
{
	delete m_setState;
	delete m_trippedState;
}

void MouseTrap::OnCurrentSquare(void* pObj)
{
	Mouse* pMouse = static_cast<Mouse*>(pObj);

	if (!m_tripped)
	{
		m_tripped = true;
		ParticleManager::Instance().CreateEmitter(EmitterType::SMOKEPUFF, m_matrix.row[2], 0.1f);
		pMouse->Thwart();
	}
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

void MouseTrap::Reset()
{
	m_matrix = MatrixIdentity();
	m_trippedState->OnExit(this);
	pState = m_setState;
	pState->OnEnter(this);
}