#include "Environment.h"
#include <TimeManager.h>
#include <BoxColliderComponent.h>
#include <memory>
#include <Helpers.h>

Environment::Environment(GameEngine::GameObject* pGameObject,const std::string& filename, GameEngine::Scene* scene):
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
void Environment::CheckCollision(Rect& shape, glm::vec2& velocity)
{
	if (m_CanCollisionBeChecked)
	{
		HitInfo hitInfo{};

		for (const auto& pBlock : m_pBlocks)
		{
			if (pBlock->IsColliding(shape, hitInfo))
			{
				ResetHorizontalPosition(velocity, shape, hitInfo);
				//m_CanCollisionBeChecked = false;
				break;
			}
		}
	}
}
void Environment::Update()
{
	glm::vec2 speed = { 5,4 };

	CheckCollision(m_pPlayer->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider(), speed);
} 
void Environment::ResetHorizontalPosition(glm::vec2& actorVelocity, Rect& actorShape,HitInfo& hitInfo) const
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

	actorVelocity.x = 0.0f;
}
