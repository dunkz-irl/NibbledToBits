#include "Play.h"
#include "Common.h"

#include "GameArea.h"
#include "GameAreaObjects.h"
#include "ParticleManager.h"

#include "Bullet.h"


Bullet::Bullet(Play::Point2f pos) : GameObject::GameObject(GameObjectType::TYPE_BULLET)
{
	m_matrix = m_matrix * Play::MatrixScale(0.75f, 0.75f);
}

void Bullet::Update()
{
	m_matrix.row[2] += m_velocity;
	m_gridPos = GameArea::WorldToGame(m_matrix.row[2]);

	GameAreaObject* obj_gameArea = GameArea::GetGameAreaObject(m_gridPos);

	if (!obj_gameArea) // outside game area
	{
		m_type = GameObjectType::TYPE_DESTROYED;
		return;
	}

	if (obj_gameArea->id == SINGLE && obj_gameArea->active)
	{
		ParticleManager::Instance().CreateEmitter(EmitterType::EXPLOSION, m_matrix.row[2], 0.1f);
		m_type = GameObjectType::TYPE_DESTROYED;
		obj_gameArea->active = false;
		obj_gameArea->vis = false;

		GameArea::ValidateAllRotatingBlockEntryDirections();
	}	
}

void Bullet::UpdateDestroyed()
{
	ParticleManager::Instance().CreateEmitter(EmitterType::SMOKEPUFFSMALL, m_matrix.row[2], 0.1f);
	m_matrix.row[2] += m_velocity;
	m_gridPos = GameArea::WorldToGame(m_matrix.row[2]);

	GameAreaObject* obj_gameArea = GameArea::GetGameAreaObject(m_gridPos);

	if (!obj_gameArea) // outside game area
	{
		ParticleManager::Instance().CreateEmitter(EmitterType::EXPLOSION, m_matrix.row[2], 0.1f);
		m_type = GameObjectType::TYPE_CLEANUP;;
	}
}

void Bullet::Draw()
{
	Play::DrawSpriteTransformed(m_spriteID, m_matrix, 0);
}
