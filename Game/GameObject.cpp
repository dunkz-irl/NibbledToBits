#include "Play.h"

#include "Time.h"
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

void GameObject::UpdateDestroyed()
{
	throw std::logic_error("UpdateDestroyed not implemented in GameObject class");
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
