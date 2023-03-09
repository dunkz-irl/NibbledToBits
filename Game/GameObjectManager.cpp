#include "Play.h"

#include "Common.h"
#include "Mouse.h"

#include "GameManager.h"

#include "GameObject.h"
#include "GameObjectManager.h"

GameObject* GameObjectManager::Create(GameObjectType type, Play::Point2f pos)
{
	GameObject* pGameObject = nullptr;

	switch (type)
	{
	case GameObjectType::TYPE_MOUSE:
		pGameObject = new Mouse(pos);
		break;

	case GameObjectType::COUNT:
		[[fallthrough]];
	default:
		PLAY_ASSERT_MSG(false, "Tried to create invalid GameObject type.");
		return nullptr;
		break;
	}

	m_v_pGameObjects.push_back(pGameObject);
	return pGameObject;
}

void GameObjectManager::UpdateAll()
{
	for (GameObject* obj : m_v_pGameObjects)
	{
		if (obj->GetGameObjectType() == GameObjectType::TYPE_DESTROYED)
		{
			obj->UpdateDestroyed();
		}
		else
		{
			obj->Update();
		}
	}
}

void GameObjectManager::DrawAll()
{
	for (GameObject* obj : m_v_pGameObjects)
	{
		obj->Draw();
	}
}

void GameObjectManager::CleanupAll()
{

}

void GameObjectManager::CleanupAllOfType(GameObjectType type)
{
	std::vector<GameObject*>::iterator it;
	for (it = m_v_pGameObjects.begin(); it != m_v_pGameObjects.end();)
	{
		GameObject* obj = *it;
		if (obj->GetGameObjectType() == type)
		{
			delete* it;
			it = m_v_pGameObjects.erase(it); // #TODO: Does this free memory? Do I need to delete it or not?
		}
		else
		{
			it++;
		}
	}
}

std::vector<GameObject*> GameObjectManager::GetGameObjectsOfType(GameObjectType type)
{
	std::vector<GameObject*> v_objs;

	for (GameObject* obj : m_v_pGameObjects)
	{
		if (obj->GetGameObjectType() == type)
		{
			v_objs.push_back(obj);
		}
	}

	return v_objs;
}
