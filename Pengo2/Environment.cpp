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
#include "EggObserver.h"

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

	auto borderBlock = BaseBlock::CreateBlock(tempCollection[0].block[0], "Border.tga", 50, false, false, 1,
		m_BorderLength, m_BorderHeight,
		glm::vec3{ tempCollection[0].block[0].x + m_BorderWidth,tempCollection[0].block[0].y + m_BorderWidth,0 });

	m_pBorderBlock = borderBlock.get();

	scene->Add(std::move(borderBlock));

	// DIAMOND BLOCKS

	int offset = 0;
	CreateBlocksCollection(m_LevelVertices, "DiamondBlock.tga", "diamond_block", offset, scene, false, false);

	//EGG BLOCKS
	CreateBlocksCollection(m_LevelVertices, "EggsBlocks.tga", "egg_block", offset, scene, true, true, 16);

	//ICE BLOCKS
	CreateBlocksCollection(m_LevelVertices, "EggsBlocks.tga", "ice_block", offset, scene, true, false, 16);

}
void Environment::CheckCollision()
{
	GameEngine::HitInfo hitInfo{};

	// CHECK ONLY FOR PLAYER WITH BLOCKS
	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{
		if (m_pBlocks[i]->IsDestroyed() || !m_pBlocks[i]) continue;

		if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsColliding(m_pPlayer, hitInfo))
		{
			m_CollisionHitInfoChanged.CreateMessage(hitInfo);
		}
	}
	//CHECK ONLY FOR PLAYER WITH BORDER
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

		// IF NOT THE SAME BLOCK
		if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetBlockIndex() == pGameObject->GetComponent<BaseBlock>()->GetBlockIndex())
		{
			continue;
		};

		// IF BLOCK MOVER HORZONTALY
		if (pGameObject->GetComponent<BaseBlock>()->GetDirection().x != 0)
		{
			// CHECK IF THERE IS SOMETHING NEARBY HORIZONTALLY
			if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(pGameObject, hitInfo))
			{
				const BlockCollisionInfo& info
				{
					pGameObject->GetComponent<BaseBlock>()->GetBlockIndex(),
					hitInfo,
					false
				};
				// NOTIFY OBSERVERS
				m_BlockCollisionInfo.CreateMessage(info);
				pGameObject->GetComponent<HitObserver>()->Notify(info.hitInfo);

				m_PushBlockIndex = -1;
			}


		}
		// IF BLOCK MOVER VERTICALLY
		else if (pGameObject->GetComponent<BaseBlock>()->GetDirection().y != 0)
		{
			// CHECK IF THERE IS SOMETHING NEARBY VERTICALLY
			if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(pGameObject, hitInfo))
			{
				const BlockCollisionInfo& info
				{
					pGameObject->GetComponent<BaseBlock>()->GetBlockIndex(),
					hitInfo,
					false
				};

				// NOTIFY OBSERVERS
				m_BlockCollisionInfo.CreateMessage(info);
				pGameObject->GetComponent<HitObserver>()->Notify(info.hitInfo);

				m_PushBlockIndex = -1;

			}
		}

		// IF BLOCK MOVES HORISONTALLY
		if (pGameObject->GetComponent<BaseBlock>()->GetDirection().x != 0)
		{
			// CHECK BORDER COLLISION HORISONTALLY
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
			// CHECK BORDER COLLISION VERTICALLY
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
			// DETACH OBSERVER
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
		// CHECK IF BLOCK COLLIDES WITH SOMETHING WHEN IT IS STATIC 
		if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(m_pPlayer, hitInfo))
		{
			if (m_pBorderBlock->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(m_pBlocks[i], hitInfo))
			{
				if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetIsBreakable())
				{
					// ONLY IF BREAKABLE
					m_pBlocks[i]->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("WasBlockDestroyed", true);

					if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetContainsEggs())
					{
						m_EggSpawnEvent.CreateMessage(m_pBlocks[i]->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition());
					}

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

						// ONLY IF BREAKABLE
						if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetContainsEggs())
						{
							m_EggSpawnEvent.CreateMessage(m_pBlocks[i]->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition());
						}

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
					// ONLY IF BREAKABLE
					m_pBlocks[i]->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("WasBlockDestroyed", true);

					if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetContainsEggs())
					{
						m_EggSpawnEvent.CreateMessage(m_pBlocks[i]->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition());
					}

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
						// ONLY IF BREAKABLE
						m_pBlocks[i]->GetComponent<GameEngine::BlackboardComponent>()->ChangeData("WasBlockDestroyed", true);

						if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetContainsEggs())
						{
							m_EggSpawnEvent.CreateMessage(m_pBlocks[i]->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition());
						}

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

void Environment::CreateBlocksCollection(std::vector<GameEngine::Block> blocks, const std::string& name,
	const std::string& tag, int& offset, GameEngine::Scene* scene, bool IsBreakable, bool containsEggs, int clipTextureAmount)
{
	std::vector<GameEngine::Block> tempCollection = GameEngine::GetBlocksWithTag(m_LevelVertices, tag);

	for (int i = 0; i < static_cast<int>(tempCollection.size()); ++i)
	{

		auto block = BaseBlock::CreateBlock(tempCollection[i].block[0], name, i + offset, IsBreakable, containsEggs, clipTextureAmount);

		if (tag == "ice_block" || tag == "egg_block")
		{
			auto textureComponent = block->GetComponent<GameEngine::TextureComponent>();

			auto textureSizeX = textureComponent->GetTexture()->GetSize().x / textureComponent->GetTextureClipAmount();
			auto textureSizeY = textureComponent->GetTexture()->GetSize().y;

			block->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });
		}

		m_BlockCollisionInfo.Attach(block->GetComponent<BlockObserver>());

		m_pBlocks.push_back(block.get());

		scene->Add(std::move(block));
	}

	offset += static_cast<int>(tempCollection.size());
}

