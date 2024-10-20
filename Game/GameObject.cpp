#include "Play.h"

#include "Time.h"
#include "Common.h"
#include "GameObject.h"


GameObject::GameObject(GameObjectType type)
{
	static int id;
	m_id = id++;

	m_type = type;
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

void GameObject::UpdateDestroyed()
{
	m_opacity -= 0.05f;

	if (m_opacity < 0)
	{
		m_type = GameObjectType::TYPE_CLEANUP;
	}
}

void GameObject::UpdateAnimation()
{
	m_frameTimer += Time::GetElapsedTime();
	if (m_frameTimer > 1.f / m_animSpeed)
	{
		m_animFrame++;
		m_frameTimer = 0.f;
	}
}

GameObjectType GameObject::GetGameObjectType()
{
	// Check for invalid GameObjectType
	PLAY_ASSERT_MSG(static_cast<int>(m_type) > 0 || static_cast<int>(m_type) < static_cast<int>(GameObjectType::COUNT), "Invalid GameObjectType");
	return m_type;
}

GridVector GameObject::GetGridPosition()
{
	return m_currentGridPosition;
}

void GameObject::SetType(GameObjectType type)
{
	if (type >= GameObjectType::COUNT || type < static_cast<GameObjectType>(0))
	{
		PLAY_ASSERT_MSG(false, "Tried to set GameObject to invalid type");
		return;
	}

	m_type = type;
}
