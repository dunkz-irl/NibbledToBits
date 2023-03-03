#include "Play.h"

#include "GameObject.h"

GameObject::GameObject()
{
	static int id;
	m_id = id++;
}

int GameObject::GetID()
{
	if (m_id != -1)
	{
		return m_id;
	}
	else
	{
		PLAY_ASSERT_MSG(false, "Tried to get invalid GameObject ID");
		return -1;
	}
}