#pragma once
#include "GameArea.h"
class CheesePickup : public GameAreaObject
{
public:
	void OnCurrentSquare(void* pObj) override;
	void Update() override;
	void Reset() override;

private:
	bool m_active{ true };
};

