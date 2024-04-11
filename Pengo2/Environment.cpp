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

				ResetHorizontalPosition(shape, hitInfo);
				//m_CanCollisionBeChecked = false;
				break;
			}
			if (pBlock->IsCollidingVertically(shape, hitInfo))
			{
				m_CollisionStateChanged.CreateMessage(GameEngine::CollisionState::Colliding);

				ResetVerticalPosition(shape, hitInfo);
				//m_CanCollisionBeChecked = false;
				break;
			}
		}
	}
}
void Environment::Update()
{
	CheckCollision(m_pPlayer->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider());
}
void Environment::ResetHorizontalPosition(Rect& actorShape, HitInfo& hitInfo) 
{
	float left = static_cast<float>(actorShape.left);

	float intersectX = static_cast<float>(hitInfo.intersectPoint.x);

	if (intersectX < left + actorShape.width / 2)
	{
		actorShape.left = static_cast<int>(intersectX);
	}
	else if (intersectX > left + actorShape.width / 2)
	{
		actorShape.left = static_cast<int>(intersectX - actorShape.width);
	}
	m_CollisionStateChanged.CreateMessage(GameEngine::CollisionState::NotColliding);
	m_pPlayer->GetComponent<GameEngine::TransformComponent>()->SetLocalPosition(glm::vec3{ actorShape.left,actorShape.bottom,0 });
}

void Environment::ResetVerticalPosition(Rect& actorShape, HitInfo& hitInfo) 
{
	float bottom = static_cast<float>(actorShape.bottom);

	float intersectY = static_cast<float>(hitInfo.intersectPoint.y);

	if (intersectY < bottom + actorShape.height / 2)
	{
		actorShape.bottom = static_cast<int>(intersectY);
	}
	else if (intersectY > bottom + actorShape.height / 2)
	{
		actorShape.bottom = static_cast<int>(intersectY - actorShape.height);
	}
	m_CollisionStateChanged.CreateMessage(GameEngine::CollisionState::NotColliding);
	m_pPlayer->GetComponent<GameEngine::TransformComponent>()->SetLocalPosition(glm::vec3{ actorShape.left,actorShape.bottom,0 });
}
