#include "Environment.h"
#include <TimeManager.h>
#include <BoxColliderComponent.h>
#include <TransformComponent.h> 
#include <ActorComponent.h>
#include <memory>
#include <Helpers.h>

Environment::Environment(GameEngine::GameObject* pGameObject, const std::string& filename, GameEngine::Scene* scene) :
	BaseComponent(pGameObject),
	m_pPlayer(nullptr)
{
	GetVerticesFromJsonFile(filename, m_VerticesIceBlocks,m_VerticesDiamondBlocks); 

	int amountOfIceBlocks = static_cast<int>(m_VerticesIceBlocks.size());
	int amountOfDiamondBlocks = static_cast<int>(m_VerticesDiamondBlocks.size());

	for (int i = 0; i < amountOfIceBlocks; ++i)
	{
		std::unique_ptr<BaseBlock> pBaseBlock = std::make_unique<BaseBlock>(m_VerticesIceBlocks[i][0], scene,"IceBlock.tga");

		m_pBlocks.push_back(std::move(pBaseBlock));
	}

	for (int i = 0; i < amountOfDiamondBlocks; ++i)
	{
		std::unique_ptr<BaseBlock> pDiamondBlock = std::make_unique<BaseBlock>(m_VerticesDiamondBlocks[i][0], scene, "DiamondBlock.tga");

		m_pBlocks.push_back(std::move(pDiamondBlock));
	}
}
void Environment::CheckCollision(Rect& shape)
{
	if (m_pPlayer->GetComponent<ActorComponent>()->GetCollisionBeChecked())
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

		m_pPlayer->GetComponent<ActorComponent>()->SetCollisionCanBeChecked(false);
	}
}
void Environment::Update()
{
	CheckCollision(m_pPlayer->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider());
}

