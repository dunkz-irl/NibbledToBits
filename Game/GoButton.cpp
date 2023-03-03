#include "Play.h"
#include "GoState.h"
#include "GoButton.h"
#include "GameManager.h"

void GoButton::Update()
{
	if (Pressed())
	{
		GM_INST.SetGameState(new GoState());
	}
}
