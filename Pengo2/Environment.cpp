#include "Environment.h"
#include "BlockComponent.h"
#include <BoxColliderComponent.h>
#include <TransformComponent.h> 
#include <ActorComponent.h>
#include <TextureComponent.h>
#include <SoundServiceLocator.h>
#include <FSM.h>
#include <Helpers.h>
#include "AnimationComponent.h"

Environment::Environment(GameEngine::GameObject* pGameObject, const std::string& filename, GameEngine::Scene* scene) :
	BaseComponent(pGameObject),
	m_pPlayer(nullptr),
	m_BorderWidth(10),
	m_BorderLength(260),
	m_BorderHeight(300)
{
	GameEngine::GetVerticesFromJsonFile(filename, m_LevelVertices);

	// BORDER 
	std::vector tempCollection = GameEngine::GetBlocksWithTag(m_LevelVertices, "border");

	auto borderBlock = BaseBlock::CreateBlock(tempCollection[0].block[0], "Border.tga", 50, false,
		m_BorderLength, m_BorderHeight,
		glm::vec3{ tempCollection[0].block[0].x + m_BorderWidth,tempCollection[0].block[0].y + m_BorderWidth,0 });

	m_pBorderBlock = borderBlock.get();

	scene->Add(std::move(borderBlock));

	// DIAMOND BLOCKS

	tempCollection = GameEngine::GetBlocksWithTag(m_LevelVertices, "diamond_block");

	int amountOfDiamondBlocks = static_cast<int>(tempCollection.size());

	for (int i = 0; i < tempCollection.size(); ++i)
	{
		auto diamondBlock = BaseBlock::CreateBlock(tempCollection[i].block[0], "DiamondBlock.tga", i, false);

		m_BlockCollisionInfo.Attach(diamondBlock->GetComponent<BlockObserver>());

		m_pBlocks.push_back(diamondBlock.get());

		scene->Add(std::move(diamondBlock));
	}

	//ICE BLOCKS
	tempCollection = GameEngine::GetBlocksWithTag(m_LevelVertices, "ice_block");

	for (int i = 0; i < tempCollection.size(); ++i)
	{
		auto iceBlock = BaseBlock::CreateBlock(tempCollection[i].block[0], "IceBlock.tga", i + amountOfDiamondBlocks);

		auto textureSizeX = iceBlock->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / 10;
		auto textureSizeY = iceBlock->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y;

		iceBlock->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });

		m_BlockCollisionInfo.Attach(iceBlock->GetComponent<BlockObserver>());

		m_pBlocks.push_back(iceBlock.get());

		scene->Add(std::move(iceBlock));
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
		if (m_pBlocks[i]->IsDestroyed()) continue;

		if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetBlockIndex() == pGameObject->GetComponent<BaseBlock>()->GetBlockIndex())
		{
			continue;
		};

		if (pGameObject->GetComponent<BaseBlock>()->GetDirection().x != 0)
		{
			if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(pGameObject, hitInfo))
			{
				const BlockCollisionInfo& info
				{
					pGameObject->GetComponent<BaseBlock>()->GetBlockIndex(),
					hitInfo,
					false
				};

				m_BlockCollisionInfo.CreateMessage(info);
				pGameObject->GetComponent<HitObserver>()->Notify(info.hitInfo);

				m_PushBlockIndex = -1;
			}


		}
		else if (pGameObject->GetComponent<BaseBlock>()->GetDirection().y != 0)
		{
			if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(pGameObject, hitInfo))
			{
				const BlockCollisionInfo& info
				{
					pGameObject->GetComponent<BaseBlock>()->GetBlockIndex(),
					hitInfo,
					false
				};

				m_BlockCollisionInfo.CreateMessage(info);
				pGameObject->GetComponent<HitObserver>()->Notify(info.hitInfo);

				m_PushBlockIndex = -1;

			}
		}

		if (pGameObject->GetComponent<BaseBlock>()->GetDirection().x != 0)
		{
			if (m_pBorderBlock->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(pGameObject, hitInfo))
			{
				const BlockCollisionInfo& info
				{
					pGameObject->GetComponent<BaseBlock>()->GetBlockIndex(),
					hitInfo,
					false
				};

				m_BlockCollisionInfo.CreateMessage(info);
				pGameObject->GetComponent<HitObserver>()->Notify(info.hitInfo);


			}
		}
		if (pGameObject->GetComponent<BaseBlock>()->GetDirection().y != 0)
		{
			if (m_pBorderBlock->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(pGameObject, hitInfo))
			{
				const BlockCollisionInfo& info
				{
					pGameObject->GetComponent<BaseBlock>()->GetBlockIndex(),
					hitInfo,
					false
				};

				m_BlockCollisionInfo.CreateMessage(info);
				pGameObject->GetComponent<HitObserver>()->Notify(info.hitInfo);

			}
		}

	}

}
void Environment::Update()
{
	CheckCollision();

	if (m_PushBlockIndex != -1)
	{
		if (m_pBlocks[m_PushBlockIndex]->IsDestroyed())
		{
			m_BlockCollisionInfo.Detach(m_pBlocks[m_PushBlockIndex]->GetComponent<BlockObserver>());

			m_PushBlockIndex = -1;
		}
	}

	if (m_PushBlockIndex != -1)
	{
		CheckBlocksCollision(m_pBlocks[m_PushBlockIndex]);
	}
}

void Environment::PushBlock()
{
	GameEngine::HitInfo hitInfo;

	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{

		if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(m_pPlayer, hitInfo))
		{
			if (m_pBorderBlock->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(m_pBlocks[i], hitInfo))
			{
				if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetIsBreakable())
				{
					m_pBlocks[i]->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("WasBlockDestroyed", true);
				}

				return;
			}

			bool canBlockBePushed = true;
			for (int j = 0; j < static_cast<int>(m_pBlocks.size()); ++j)
			{
				if (m_pBlocks[i] == m_pBlocks[j]) continue;
				if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(m_pBlocks[j], hitInfo))
				{
					if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetIsBreakable())
					{
						m_pBlocks[i]->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("WasBlockDestroyed", true);
					}

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
			m_PushBlockIndex = i;
			break;
		}

		if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(m_pPlayer, hitInfo))
		{
			if (m_pBorderBlock->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(m_pBlocks[i], hitInfo))
			{
				if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetIsBreakable())
				{
					m_pBlocks[i]->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("WasBlockDestroyed", true);

				}
				return;
			}
			bool canBlockBePushed = true;

			for (int j = 0; j < static_cast<int>(m_pBlocks.size()); ++j)
			{
				if (m_pBlocks[i] == m_pBlocks[j]) continue;

				if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(m_pBlocks[j], hitInfo))
				{
					canBlockBePushed = false;
					if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetIsBreakable())
					{
						m_pBlocks[i]->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("WasBlockDestroyed", true);

					}
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
			m_PushBlockIndex = i;
			break;
		}
	}

}

