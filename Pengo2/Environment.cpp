#include "Environment.h"
#include <TimeManager.h>
#include <BoxColliderComponent.h>
#include <TransformComponent.h> 
#include <ActorComponent.h>
#include <memory>
#include <Helpers.h>

Environment::Environment(GameEngine::GameObject* pGameObject, const std::string& filename, GameEngine::Scene* scene) :
	BaseComponent(pGameObject),
	m_CanCollisionBeChecked(true),
	m_pPlayer(nullptr)
{
	GetVerticesFromJsonFile(filename, m_Vertices);

	int amountOfBlocks = static_cast<int>(m_Vertices.size());

	for (int i = 0; i < amountOfBlocks; ++i)
	{
		std::unique_ptr<BaseBlock> pBaseBlock = std::make_unique<BaseBlock>(m_Vertices[i][0], scene);

		m_pBlocks.push_back(std::move(pBaseBlock));
	}
}
void Environment::CheckCollision(Rect& shape)
{
	if (m_CanCollisionBeChecked)
	{
		HitInfo hitInfo{};

		for (const auto& pBlock : m_pBlocks)
		{
			if (pBlock->IsCollidingHorizontally(shape, hitInfo))
			{
				m_CollisionStateChanged.CreateMessage(GameEngine::CollisionState::Colliding);
				m_CollisionHitInfoChanged.CreateMessage(hitInfo);
				m_CollisionStateChanged.CreateMessage(GameEngine::CollisionState::NotColliding);
				break;
			}
			if (pBlock->IsCollidingVertically(shape, hitInfo))
			{
				m_CollisionStateChanged.CreateMessage(GameEngine::CollisionState::Colliding);
				m_CollisionHitInfoChanged.CreateMessage(hitInfo);
				m_CollisionStateChanged.CreateMessage(GameEngine::CollisionState::NotColliding); 
				break;
			}
		}

		//m_CanCollisionBeChecked = false;
	}
}
void Environment::Update()
{
	CheckCollision(m_pPlayer->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider());
}

