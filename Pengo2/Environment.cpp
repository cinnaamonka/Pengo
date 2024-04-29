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

	BaseBlock* const currentBaseBlock = pGameObject->GetComponent<BaseBlock>();
	HitObserver* const currentHitObserver = pGameObject->GetComponent<HitObserver>();

	const bool isMovingHorizontally = currentBaseBlock->GetDirection().x != 0;
	const bool isMovingVertically = currentBaseBlock->GetDirection().y != 0;

	bool collisionDetected = false;

	for (GameEngine::GameObject* const block : m_pBlocks)
	{
		if (block->IsDestroyed()) continue;

		BaseBlock* const blockBaseBlock = block->GetComponent<BaseBlock>();

		if (blockBaseBlock->GetBlockIndex() == currentBaseBlock->GetBlockIndex()) continue;

		CollisionComponent* const collisionComponent = block->GetComponent<CollisionComponent>();

		const bool isCollidingHorizontally = isMovingHorizontally && collisionComponent->IsBlockNearbyHorizontally(pGameObject, hitInfo);
		const bool isCollidingVertically = isMovingVertically && collisionComponent->IsBlockNearbyVertically(pGameObject, hitInfo);

		if (isCollidingHorizontally || isCollidingVertically)
		{
			collisionDetected = true;
			break;
		}
	}

	if (!collisionDetected)
	{
		CollisionComponent* const borderCollisionComponent = m_pBorderBlock->GetComponent<CollisionComponent>();

		const bool isCollidingHorizontallyWithBorder = isMovingHorizontally && borderCollisionComponent->IsBlockNearbyHorizontally(pGameObject, hitInfo);
		const bool isCollidingVerticallyWithBorder = isMovingVertically && borderCollisionComponent->IsBlockNearbyVertically(pGameObject, hitInfo);

		if (isCollidingHorizontallyWithBorder || isCollidingVerticallyWithBorder)
		{
			collisionDetected = true;
		}
	}

	if (collisionDetected)
	{
		NotifyCollision(currentBaseBlock->GetBlockIndex(), hitInfo, currentHitObserver);
		PlayCollisionSound();
	}
}



void Environment::NotifyCollision(int blockIndex, const GameEngine::HitInfo& hitInfo, HitObserver* hitObserver, bool isPushed, int pushBlockIndex)
{
	const BlockCollisionInfo info{
		blockIndex,
		hitInfo,
		isPushed
	};

	m_BlockCollisionInfo.CreateMessage(info);

	if (hitObserver)
	{
		hitObserver->Notify(info.hitInfo);
	}

	m_PushBlockIndex = pushBlockIndex;
}

void Environment::PlayCollisionSound()
{
	auto& soundSystem = GameEngine::SoundServiceLocator::GetSoundSystemInstance();
	soundSystem.Load("../Data/Sound/test.wav", 0);
	soundSystem.Play(0, 20.f);
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
		GameEngine::TransformComponent* const transformComponent = m_pBlocks[i]->GetComponent<GameEngine::TransformComponent>();
		GameEngine::BlackboardComponent* const blackboardComponent = m_pBlocks[i]->GetComponent<GameEngine::BlackboardComponent>();

		CollisionComponent* const blockCollisionComponent = m_pBlocks[i]->GetComponent<CollisionComponent>();
		CollisionComponent* const borderCollisionComponent = m_pBorderBlock->GetComponent<CollisionComponent>();

		BaseBlock* const baseBlockComponent = m_pBlocks[i]->GetComponent<BaseBlock>();

		bool isBlockNearbyPlayerVertically = blockCollisionComponent->IsBlockNearbyVertically(m_pPlayer, hitInfo);
		const bool isBlockNearbyBorderVertically = borderCollisionComponent->IsBlockNearbyVertically(m_pBlocks[i], hitInfo);

		bool isBlockNearbyPlayerHorizontally = blockCollisionComponent->IsBlockNearbyHorizontally(m_pPlayer, hitInfo);
		const bool isBlockNearbyBorderHorizontally = borderCollisionComponent->IsBlockNearbyHorizontally(m_pBlocks[i], hitInfo);

		const bool isBlockBreakable = baseBlockComponent->GetIsBreakable();
		const bool hasEggs = baseBlockComponent->GetContainsEggs();

		if ((isBlockNearbyPlayerVertically && isBlockNearbyBorderVertically) ||
			(isBlockNearbyPlayerHorizontally && isBlockNearbyBorderHorizontally))
		{
			if (isBlockBreakable)
			{
				blackboardComponent->ChangeData("WasBlockDestroyed", true);

				if (hasEggs)
				{
					m_EggSpawnEvent.CreateMessage(transformComponent->GetLocalPosition());
				}
			}

			return;
		}

		isBlockNearbyPlayerVertically = blockCollisionComponent->IsBlockNearbyVertically(m_pPlayer, hitInfo);
		isBlockNearbyPlayerHorizontally = blockCollisionComponent->IsBlockNearbyHorizontally(m_pPlayer, hitInfo);

		if (isBlockNearbyPlayerVertically || isBlockNearbyPlayerHorizontally)
		{
			bool canBlockBePushed = true;

			for (int j = 0; j < static_cast<int>(m_pBlocks.size()); ++j)
			{
				if (m_pBlocks[i] == m_pBlocks[j]) continue;

				const bool isBlockNearby = isBlockNearbyPlayerVertically ? blockCollisionComponent->IsBlockNearbyVertically(m_pBlocks[j], hitInfo) : 
					                                                       blockCollisionComponent->IsBlockNearbyHorizontally(m_pBlocks[j], hitInfo);
				if (isBlockNearby && isBlockBreakable)
				{
					blackboardComponent->ChangeData("WasBlockDestroyed", true);

					if (hasEggs)
					{
						m_EggSpawnEvent.CreateMessage(transformComponent->GetLocalPosition());
					}

					canBlockBePushed = false;
					break;
				}
			}

			if (!canBlockBePushed) return;

			NotifyCollision(i, hitInfo, nullptr, true, i);

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

