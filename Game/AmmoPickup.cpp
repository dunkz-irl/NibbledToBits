#include "Play.h"

#include <queue>
#include "Tank.h"
#include "ParticleManager.h"
#include "ParticlesCommon.h"
#include "Time.h"

#include "AmmoPickup.h"

extern std::vector<std::string> g_v_idToStringTable;

void AmmoPickup::Update()
{
	if (m_active)
	{
		float t = Time::GetOverallTime() + Magnitude({ posx, posy });
		t *= 8.f;

		m_matrix = MatrixScale(sin(t) / 10.f + 1.f, cos(t) / 10.f + 1.f);

		m_matrix.row[2] = GameArea::GameToWorld({ posx, posy });
	}
}

void AmmoPickup::OnCurrentSquare(void* pObj)
{
	if (m_active)
	{
		m_active = false;
		vis = false;
		
		std::string itemName = g_v_idToStringTable[GameAreaObject::id];
		auto it_end = itemName.end();
		itemName.erase(it_end - 1);
		itemName += "_RA";

		PM_INST.CreateEmitter(EmitterType::SMOKEPUFFSMALL, m_matrix.row[2], 0.1f);

		Tank::AddAmmo(Play::GetSpriteId(itemName.c_str()));
	}
}

void AmmoPickup::Reset()
{
	m_active = true;
	vis = true;
}
