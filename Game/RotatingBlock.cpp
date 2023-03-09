#include "Play.h"
#include "RotatingBlock.h"
#include "Common.h"
#include "Mouse.h"
#include <array>

void RotatingBlock::OnCurrentSquare(void* mouse)
{
	Mouse* obj_mouse = static_cast<Mouse*>(mouse);
	std::array<bool, 4> validDirections = GameArea::GetBlockValidDirections(*obj_mouse->m_currentGridObj);

	// Mouse can't go back the way it came

	int directionIndex = static_cast<int>(obj_mouse->GetCurrentDirectionEnum());
	directionIndex += 2; // Get opposite direction
	directionIndex %= 4; // Wrap around

	validDirections[directionIndex] = false;

	for (int i = 0; i < 4; i++)
	{
		if (validDirections[i])
		{
			obj_mouse->m_currentDirection = obj_mouse->m_directionVectors[i];
			obj_mouse->m_matrix.row[2] = GameArea::GameToWorld({ obj_mouse->m_currentGridObj->posx, obj_mouse->m_currentGridObj->posy }); // Align mouse
			obj_mouse->UpdateTrackedGridSquares();
			break;
		}
	}
}

void RotatingBlock::OnNextSquare(void* mouse)
{
	Mouse* obj_mouse = static_cast<Mouse*>(mouse);

	// Mouse should only reverse once per behaviour update
	bool reversed = false;

	std::array<bool, 4> validEntrances = GameArea::GetBlockValidDirections(*obj_mouse->m_nextGridObj);

	// Check entrance mouse is facing to see if valid;
	GridDirection currentDir = obj_mouse->GetCurrentDirectionEnum();

	// Get opposite entrance to the direction mouse is facing/travelling
	if (!validEntrances[(static_cast<int>(currentDir) + 2) % 4]) 
	{
		if (!reversed)
		{
			obj_mouse->ReverseDirection();
			obj_mouse->UpdateTrackedGridSquares();
			reversed = true;
		}
	}

	// If only 1 entrance, reverse direction as mouse can't get out.
	int count = 0;
	for (bool entr : validEntrances)
	{
		if (entr)
			count++;
	}

	if (count == 0 || count == 1)
	{
		if (!reversed)
		{
			obj_mouse->ReverseDirection();
			obj_mouse->UpdateTrackedGridSquares();
			reversed = true;
		}
	}
}