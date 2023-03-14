#include "Play.h"
#include "Common.h"

#include "Mouse.h"
#include "GameManager.h"
#include "ParticleManager.h"
#include "EasingFunctions.h"
#include "Time.h"

#include "CheesePickup.h"

void CheesePickup::OnCurrentSquare(void* pObj)
{
	if (!m_active)
		return;

	vis = false;
	m_active = false;
	Mouse* pMouse = static_cast<Mouse*>(pObj);

	GridVector mousePos = pMouse->GetGridPosition();
	// GM_INST.RemoveGameAreaObject(mousePos);


	ParticleManager::Instance().CreateEmitter(EmitterType::CHEESE, GameArea::GameToWorld({ mousePos.x, mousePos.y }), 0.2f);

	GM_INST.IncrementCollectedCheese();
}

void CheesePickup::Update()
{
	if (m_active)
	{
		float t = Time::GetOverallTime();
		t *= 8.f;

		m_matrix = MatrixScale(sin(t) / 10.f + 1.f, cos(t) / 10.f + 1.f);

		m_matrix.row[2] = GameArea::GameToWorld({ posx, posy });
	}

	// m_matrix.row[2] = GameArea::GameToWorld({ posx, posy });
}

void CheesePickup::Reset()
{
	m_active = true;
	vis = true;
}
