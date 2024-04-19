#include "Environment.h"
#include <TimeManager.h>
#include "BlockComponent.h"
#include <BoxColliderComponent.h>
#include <TransformComponent.h> 
#include <ActorComponent.h>
#include <memory>
#include <Helpers.h>

Environment::Environment(GameEngine::GameObject* pGameObject, const std::string& filename, GameEngine::Scene* scene) :
	BaseComponent(pGameObject),
	m_pPlayer(nullptr),
	m_PushDirection{},
	m_PushedBlockIndex{},
	m_BlockCanBePushed(false)
{
	GetVerticesFromJsonFile(filename, m_VerticesIceBlocks, m_VerticesDiamondBlocks);

	int amountOfIceBlocks = static_cast<int>(m_VerticesIceBlocks.size());
	int amountOfDiamondBlocks = static_cast<int>(m_VerticesDiamondBlocks.size());

	for (int i = 0; i < amountOfDiamondBlocks; ++i)
	{
		std::unique_ptr<BaseBlock> pDiamondBlock = std::make_unique<BaseBlock>(m_VerticesDiamondBlocks[i][0], scene, "DiamondBlock.tga");
		m_pBlocks.push_back(std::move(pDiamondBlock));

	}
	for (int i = 0; i < amountOfIceBlocks; ++i)
	{
		auto position = m_VerticesIceBlocks[i][0];
		bool positionExists = std::find_if(m_pBlocks.begin(), m_pBlocks.end(),
			[&position](const std::unique_ptr<BaseBlock>& block)
			{
				return block->GetPosition() == position;
			}) != m_pBlocks.end();

			if (!positionExists)
			{
				std::unique_ptr<BaseBlock> pBaseBlock = std::make_unique<BaseBlock>(position, scene, "IceBlock.tga");
				m_pBlocks.push_back(std::move(pBaseBlock));
			}
	}
}
void Environment::CheckCollision(Rect& shape)
{
	if (m_pPlayer->GetComponent<ActorComponent>()->GetCollisionBeChecked())
	{
		HitInfo hitInfo{};

		for (int i = 0; i < m_pBlocks.size(); ++i)
		{
			if (m_pBlocks[i]->IsCollidingHorizontally(shape, hitInfo))
			{
				m_CollisionHitInfoChanged.CreateMessage(hitInfo);
				m_PushedBlockIndex = i;
				m_PushDirection = { hitInfo.normal.x,0,0 };
				m_pBlocks[m_PushedBlockIndex]->SetPushSpeed(10.0f);
				break;
			}
			if (m_pBlocks[i]->IsCollidingVertically(shape, hitInfo))
			{
				m_CollisionHitInfoChanged.CreateMessage(hitInfo);
				m_PushedBlockIndex = i;
				m_PushDirection = { 0,hitInfo.normal.y,0 };
				m_pBlocks[m_PushedBlockIndex]->SetPushSpeed(10.0f);
				break;
			}
		}

		m_pPlayer->GetComponent<ActorComponent>()->SetCollisionCanBeChecked(false);
	}
}
void Environment::CheckBlocksCollision(Rect& shape)
{

	HitInfo hitInfo{};

	for (int i = 0; i < m_pBlocks.size(); ++i)
	{
		if (m_pBlocks[i]->IsCollidingHorizontally(shape, hitInfo))
		{
			if (i != m_PushedBlockIndex)
			{
				m_BlockCanBePushed = false;
				m_pBlocks[m_PushedBlockIndex]->SetPushSpeed(0);
				m_pBlocks[m_PushedBlockIndex]->GetHitObserver()->Notify(hitInfo);
				break;
			}

		}  
		
		if (m_pBlocks[i]->IsCollidingVertically(shape, hitInfo))
		{
			if (i != m_PushedBlockIndex)
			{
				m_BlockCanBePushed = false;
				m_pBlocks[m_PushedBlockIndex]->SetPushSpeed(0);
				m_pBlocks[m_PushedBlockIndex]->GetHitObserver()->Notify(hitInfo);
				break;
			}
		}
	}
}
void Environment::Update()
{
	CheckCollision(m_pPlayer->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider());

	if (m_BlockCanBePushed)
	{
		m_pBlocks[m_PushedBlockIndex]->PushBlock(m_PushDirection);
		CheckBlocksCollision(m_pBlocks[m_PushedBlockIndex]->GetBlockShape());
	}
}

void Environment::PushBlock()
{
	if (m_pBlocks[m_PushedBlockIndex]->GetPushSpeed() != 0)
	{
		m_BlockCanBePushed = true;
	}
	

}

