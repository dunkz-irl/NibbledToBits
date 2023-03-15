#include "Play.h"

#include <queue>
#include "Tank.h"
#include "ParticleManager.h"

#include "AmmoPickup.h"

extern std::vector<std::string> g_v_idToStringTable;

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
