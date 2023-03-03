#include "Play.h"

#include "Mouse.h"

#include "GameManager.h"

#include "GameObject.h"
#include "GameObjectFactory.h"

GameObject* GameObjectFactory::Create(GameObjectType type, Play::Point2f pos)
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

	GM_INST.m_vGameObjectIDs.push_back(pGameObject->GetID());
	return pGameObject;
}