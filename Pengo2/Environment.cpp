#include "Environment.h"
#include <TimeManager.h>
#include "BlockComponent.h"
#include <BoxColliderComponent.h>
#include <TransformComponent.h> 
#include <ActorComponent.h>
#include <TextureComponent.h>
#include <SoundServiceLocator.h>
#include <memory>
#include <FSM.h>
#include <Helpers.h>
#include "AnimationComponent.h"
#include <LifetimeObserver.h>

Environment::Environment(GameEngine::GameObject* pGameObject, const std::string& filename, GameEngine::Scene* scene) :
	BaseComponent(pGameObject),
	m_pPlayer(nullptr),
	m_BorderWidth(10),
	m_BorderLength(260),
	m_BorderHeight(300)
{
	GameEngine::GetVerticesFromJsonFile(filename, m_VerticesIceBlocks, m_VerticesDiamondBlocks, m_BorderVertices);

	auto borderBlock = BaseBlock::CreateBlock(m_BorderVertices[0][0], "Border.tga", 50,
		m_BorderLength, m_BorderHeight,
		glm::vec3{ m_BorderVertices[0][0].x + m_BorderWidth,m_BorderVertices[0][0].y + m_BorderWidth,0 });

	m_pBorderBlock = borderBlock.get();
	scene->Add(std::move(borderBlock));
	
	int amountOfIceBlocks = static_cast<int>(m_VerticesIceBlocks.size());
	int amountOfDiamondBlocks = static_cast<int>(m_VerticesDiamondBlocks.size());

	for (int i = 0; i < amountOfDiamondBlocks; ++i)
	{
		auto diamondBlock = BaseBlock::CreateBlock(m_VerticesDiamondBlocks[i][0], "DiamondBlock.tga", i);

		m_BlockCollisionInfo.Attach(diamondBlock->GetComponent<BlockObserver>());

		m_pBlocks.push_back(diamondBlock.get());

		scene->Add(std::move(diamondBlock));
	}
	for (int i = 0; i < amountOfIceBlocks; ++i)
	{
		auto position = m_VerticesIceBlocks[i][0];
		bool positionExists = std::find_if(m_pBlocks.begin(), m_pBlocks.end(),
			[&position](const auto& block)
			{
				return block->GetComponent<BaseBlock>()->GetPosition() == position;
			}) != m_pBlocks.end();

			if (!positionExists)
			{
				auto iceBlock = BaseBlock::CreateBlock(position, "IceBlock.tga", i + amountOfDiamondBlocks);
				auto textureSizeX = iceBlock->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / 10;
				auto textureSizeY = iceBlock->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y;

				iceBlock->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });
				m_BlockCollisionInfo.Attach(iceBlock->GetComponent<BlockObserver>());

				m_pBlocks.push_back(iceBlock.get());
				scene->Add(std::move(iceBlock));
			}
	}

}
void Environment::CheckCollision()
{
	GameEngine::HitInfo hitInfo{};

	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{
		if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsColliding(m_pPlayer, hitInfo))
		{
			m_CollisionHitInfoChanged.CreateMessage(hitInfo);
		}

	}

	if (m_pBorderBlock->GetComponent<CollisionComponent>()->IsColliding(m_pPlayer, hitInfo))
	{
		m_CollisionHitInfoChanged.CreateMessage(hitInfo);
	}
}

void Environment::CheckBlocksCollision(GameEngine::GameObject* pGameObject)
{
	GameEngine::HitInfo hitInfo{};
	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{
		if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetBlockIndex() == pGameObject->GetComponent<BaseBlock>()->GetBlockIndex())
		{
			continue;
		};

		if (pGameObject->GetComponent<BaseBlock>()->GetDirection().x != 0)
		{
			if(m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(pGameObject, hitInfo))
			{
				const BlockCollisionInfo& info
				{
					pGameObject->GetComponent<BaseBlock>()->GetBlockIndex(),
					hitInfo,
					false
				};

				m_BlockCollisionInfo.CreateMessage(info);
				pGameObject->GetComponent<HitObserver>()->Notify(info.hitInfo);


				auto it = std::find(m_PushedBlocksIndexes.begin(), m_PushedBlocksIndexes.end(), pGameObject->GetComponent<BaseBlock>()->GetBlockIndex());
				m_PushedBlocksIndexes.erase(it); 
			}
		}
		else if (pGameObject->GetComponent<BaseBlock>()->GetDirection().y != 0)
		{
			if(m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(pGameObject, hitInfo))
			{
				const BlockCollisionInfo& info
				{
					pGameObject->GetComponent<BaseBlock>()->GetBlockIndex(),
					hitInfo,
					false
				};

				m_BlockCollisionInfo.CreateMessage(info);
				pGameObject->GetComponent<HitObserver>()->Notify(info.hitInfo);
	

				auto it = std::find(m_PushedBlocksIndexes.begin(), m_PushedBlocksIndexes.end(), pGameObject->GetComponent<BaseBlock>()->GetBlockIndex());
				m_PushedBlocksIndexes.erase(it);
			}
		}

		if (pGameObject->GetComponent<BaseBlock>()->GetDirection().x != 0)
		{
			if (m_pBorderBlock->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(pGameObject, hitInfo))
			{
				const BlockCollisionInfo& info
				{
					0,
					hitInfo,
					false
				};

				m_BlockCollisionInfo.CreateMessage(info);
				pGameObject->GetComponent<HitObserver>()->Notify(info.hitInfo); 


				auto it = std::find(m_PushedBlocksIndexes.begin(), m_PushedBlocksIndexes.end(), pGameObject->GetComponent<BaseBlock>()->GetBlockIndex());
				m_PushedBlocksIndexes.erase(it);
			}
		}
		else if (pGameObject->GetComponent<BaseBlock>()->GetDirection().y != 0)
		{
			if (m_pBorderBlock->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(pGameObject, hitInfo))
			{
				const BlockCollisionInfo& info
				{
					0,
					hitInfo,
					false
				};

				m_BlockCollisionInfo.CreateMessage(info);
				pGameObject->GetComponent<HitObserver>()->Notify(info.hitInfo);


				auto it = std::find(m_PushedBlocksIndexes.begin(), m_PushedBlocksIndexes.end(), pGameObject->GetComponent<BaseBlock>()->GetBlockIndex());
				m_PushedBlocksIndexes.erase(it);
			}
		}

	}

}
void Environment::Update()
{
	CheckCollision();
	
	if(!m_PushedBlocksIndexes.empty())
	{
		for (auto boxIndex : m_PushedBlocksIndexes)
		{
			CheckBlocksCollision(m_pBlocks[boxIndex]);
		}
	}

	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{
		if (m_pBlocks[i]->IsDestroyed())
		{
			m_pBlocks.erase(m_pBlocks.begin() + i);
			
			m_BlockCollisionInfo.Detach(m_pBlocks[i]->GetComponent<BlockObserver>());

			continue;
		}
	}
}

void Environment::PushBlock()
{
	GameEngine::HitInfo hitInfo;

	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{
		
		if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(m_pPlayer, hitInfo))
		{
			bool canBlockBePushed = true;
			for (int j = 0; j < static_cast<int>(m_pBlocks.size()); ++j)
			{
				if(m_pBlocks[i] == m_pBlocks[j]) continue;
				if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(m_pBlocks[j], hitInfo))
				{
					m_pBlocks[i]->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("WasBlockDestroyed", true);
					canBlockBePushed = false;
					break;
				}
			}
			if (!canBlockBePushed) return;
			
			const BlockCollisionInfo& info
			{
				i,
				hitInfo,
				true
			};

			m_BlockCollisionInfo.CreateMessage(info);
			m_PushedBlocksIndexes.push_back(i);
			break;
		}
	
		if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(m_pPlayer, hitInfo))
		{

			bool canBlockBePushed = true;
			
			for (int j = 0; j < static_cast<int>(m_pBlocks.size()); ++j)
			{
				if (m_pBlocks[i] == m_pBlocks[j]) continue;

				if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(m_pBlocks[j], hitInfo))
				{
					canBlockBePushed = false;
					m_pBlocks[i]->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("WasBlockDestroyed", true);
					break;
				}
			}
			if (!canBlockBePushed) return;
			const BlockCollisionInfo& info
			{
				i,
				hitInfo,
				true
			};

			m_BlockCollisionInfo.CreateMessage(info);
			m_PushedBlocksIndexes.push_back(i);
			break;
		}
	}
}

