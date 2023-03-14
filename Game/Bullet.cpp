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
	// throw std::logic_error("The method or operation is not implemented.");
	m_gridPos = GameArea::WorldToGame(m_matrix.row[2]);

	GameAreaObject* obj_gameArea = GameArea::GetGameAreaObject(m_gridPos);

	if (!obj_gameArea) // outside game area
	{
		m_type = GameObjectType::TYPE_DESTROYED;
		return;
	}

	if (obj_gameArea->id == SINGLE)
	{
		ParticleManager::Instance().CreateEmitter(EmitterType::CONFETTI, m_matrix.row[2], 0.1f);
		m_type = GameObjectType::TYPE_DESTROYED;
	}	
}

void Bullet::UpdateDestroyed()
{
	ParticleManager::Instance().CreateEmitter(EmitterType::SMOKEPUFFSMALL, m_matrix.row[2], 0.1f);
	m_matrix.row[2] += m_velocity;
	// throw std::logic_error("The method or operation is not implemented.");
	m_gridPos = GameArea::WorldToGame(m_matrix.row[2]);

	GameAreaObject* obj_gameArea = GameArea::GetGameAreaObject(m_gridPos);

	if (!obj_gameArea) // outside game area
	{
		ParticleManager::Instance().CreateEmitter(EmitterType::CONFETTI, m_matrix.row[2], 0.1f);
		m_type = GameObjectType::TYPE_CLEANUP;;
	}
}

void Bullet::Draw()
{
	Play::DrawSpriteTransformed(Play::GetSpriteId("sunflowerseed_RA"), m_matrix, 0);

	// throw std::logic_error("The method or operation is not implemented.");
}
