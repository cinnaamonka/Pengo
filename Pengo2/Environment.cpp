
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
#include "EnemyManager.h"
#include "EggObserver.h"
#include "Structs.h"

Environment::Environment(GameEngine::GameObject* pGameObject, const std::string& filename, GameEngine::Scene* scene) :
	BaseComponent(pGameObject),
	m_pPlayer(nullptr),
	m_BorderWidth(10),
	m_BorderLength(260),
	m_BorderHeight(300)
{
	GameEngine::GetVerticesFromJsonFile(filename, m_LevelVertices);

	std::vector tempCollection = GameEngine::GetBlocksWithTag(m_LevelVertices, "border");

	auto borderBlock = BaseBlock::CreateBlock(tempCollection[0].block[0], "Border.tga", 50, false, false, false, false, 1,
		m_BorderLength, m_BorderHeight,
		glm::vec3{ tempCollection[0].block[0].x + m_BorderWidth,tempCollection[0].block[0].y + m_BorderWidth,0 });

	m_pBorderBlock = borderBlock.get();

	scene->Add(std::move(borderBlock));

	int offset = 0;
	CreateBlocksCollection(m_LevelVertices, "DiamondBlock.tga", "diamond_block", offset, scene, false, false, false, true);

	CreateBlocksCollection(m_LevelVertices, "EggsBlocks.tga", "egg_block", offset, scene, true, true, false, false, 16);

	CreateBlocksCollection(m_LevelVertices, "EggsBlocks.tga", "ice_block", offset, scene, true, false, false, false, 16);
	CreateBlocksCollection(m_LevelVertices, "EggsBlocks.tga", "enemy_block", offset, scene, true, false, true, false, 16);

	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{
		if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetIsDiamondBlock())
		{
			m_DiamondBlocksPositions.insert({ i,m_pBlocks[i]->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition() });
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

	const auto borderCollisionComponent = m_pBorderBlock->GetComponent<CollisionComponent>();

	if (borderCollisionComponent->IsColliding(m_pPlayer, hitInfo))
	{
		m_CollisionHitInfoChanged.CreateMessage(hitInfo);
	}


}

void Environment::CheckBlocksCollision(GameEngine::GameObject* pGameObject)
{
	GameEngine::HitInfo hitInfo{};
	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{
		auto currentBlock = m_pBlocks[i]->GetComponent<BaseBlock>();

		if (currentBlock->GetBlockIndex() == pGameObject->GetComponent<BaseBlock>()->GetBlockIndex())continue;

		auto collisionComponent = m_pBlocks[i]->GetComponent<CollisionComponent>();

		if (pGameObject->GetComponent<BaseBlock>()->GetDirection().x != 0)
		{
			if (collisionComponent->IsBlockNearbyHorizontally(pGameObject, hitInfo) ||
				m_pBorderBlock->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(pGameObject, hitInfo))
			{
				StopBlock(pGameObject, hitInfo);
			}
		}
		if (pGameObject->GetComponent<BaseBlock>()->GetDirection().y != 0)
		{
			if (collisionComponent->IsBlockNearbyVertically(pGameObject, hitInfo) ||
				m_pBorderBlock->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(pGameObject, hitInfo))
			{
				StopBlock(pGameObject, hitInfo);
			}
		}
	}
}

void Environment::Update()
{
	CheckEnemiesCollision();

	if (!m_pPlayer->GetComponent<GameEngine::ActorComponent>()->GetCollisionBeChecked()) return;

	CheckCollision();

	if (m_PushBlockIndex != -1)
	{
		CheckBlocksCollision(m_pBlocks[m_PushBlockIndex]);

		if (m_PushBlockIndex != -1)
		{
			m_pEnemyManager->CheckCollisionWithPushedBlock(m_pBlocks[m_PushBlockIndex]);
		}

	}
}

void Environment::PushBlock()
{
	GameEngine::HitInfo hitInfo;

	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{

		bool verticalCollision = m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(m_pPlayer, hitInfo);
		bool horizontalCollision = m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(m_pPlayer, hitInfo);

		if (verticalCollision || horizontalCollision)
		{
			if ((verticalCollision && m_pBorderBlock->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(m_pBlocks[i], hitInfo)) ||
				(horizontalCollision && m_pBorderBlock->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(m_pBlocks[i], hitInfo)))
			{
				BreakBlock(i);
				return;
			}

			bool canBlockBePushed = true;

			for (int j = 0; j < static_cast<int>(m_pBlocks.size()); ++j)
			{
				if (i != j && ((verticalCollision && m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(m_pBlocks[j], hitInfo)) ||
					(horizontalCollision && m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(m_pBlocks[j], hitInfo))))
				{
					BreakBlock(i);
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

			GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().Play(static_cast<int>(PengoSounds::BlockPushed), 20);
		}
	}
}

void Environment::CreateBlocksCollection(std::vector<GameEngine::Block> blocks, const std::string& name,
	const std::string& tag, int& offset, GameEngine::Scene* scene, bool IsBreakable, bool containsEggs,
	bool shouldBreakOnSpot, bool isDiamondBlock, int clipTextureAmount)
{
	std::vector<GameEngine::Block> tempCollection = GameEngine::GetBlocksWithTag(m_LevelVertices, tag);

	for (int i = 0; i < static_cast<int>(tempCollection.size()); ++i)
	{
		auto block = BaseBlock::CreateBlock(tempCollection[i].block[0], name, i + offset, IsBreakable, containsEggs, isDiamondBlock, shouldBreakOnSpot, clipTextureAmount);

		if (tag == "ice_block" || tag == "egg_block" || tag == "enemy_block")
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
void Environment::StopBlock(GameEngine::GameObject* block, GameEngine::HitInfo hitInfo)
{
	auto index = block->GetComponent<BaseBlock>()->GetBlockIndex();

	const BlockCollisionInfo& info
	{
		index,
		hitInfo,
		false
	};

	

	m_BlockCollisionInfo.CreateMessage(info);
	block->GetComponent<HitObserver>()->Notify(info.hitInfo);

	m_PushBlockIndex = -1;

	if (m_pBlocks[index]->GetComponent<BaseBlock>()->GetIsDiamondBlock())
	{
		m_EnvEvent.CreateMessage(EventInfo{ Event::DiamondBlockChangedPos });
	}
}
void Environment::BreakBlock(int index)
{
	if (m_pBlocks[index]->GetComponent<BaseBlock>()->GetIsBreakable())
	{
		m_pBlocks[index]->GetComponent<GameEngine::AnimationComponent>()->SetIsDestroyed(true);

		m_BlockCollisionInfo.Detach(m_pBlocks[index]->GetComponent<BlockObserver>());

		if (m_pBlocks[index]->GetComponent<BaseBlock>()->GetContainsEggs())
		{
			auto position = m_pBlocks[index]->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();
			m_EggSpawnEvent.CreateMessage(position);
			m_ScoreAppearingEvent.CreateMessage(Score{ ScoreType::EggFound, position });
			m_AddingScoreInHUDEvent.CreateMessage(GameEngine::HUDEvent::InceaseScore500);
			GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().Play(static_cast<int>(PengoSounds::SnoBeeEggDestroyed), 20);
		}
		else
		{
			m_AddingScoreInHUDEvent.CreateMessage(GameEngine::HUDEvent::IncreaseScore30);
			GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().Play(static_cast<int>(PengoSounds::IceBlockDestroyed), 20);
		}

		m_pBlocks.erase(m_pBlocks.begin() + index);
		m_PushBlockIndex = -1;
		m_EnvEvent.CreateMessage(Event::BlockIndexesChanged);

	}
}

void Environment::CheckDiamondBlocksPositions()
{
	if (GameEngine::AreThreePointsOnSameLine(m_DiamondBlocksPositions[0], m_DiamondBlocksPositions[1], m_DiamondBlocksPositions[2]))
	{
		m_AddingScoreInHUDEvent.CreateMessage(GameEngine::HUDEvent::IncreaseScore30); 
		GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().Play(static_cast<int>(PengoSounds::DiamondBlocksLinedUp), 20); 
	}
}

void Environment::ResetBlocksIndexes()
{
	m_DiamondBlocksPositions.clear();

	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{
		if (!m_pBlocks[i]->IsDestroyed())
		{
			m_pBlocks[i]->GetComponent<BaseBlock>()->SetBlockIndex(i);

			if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetIsDiamondBlock())
			{
				m_DiamondBlocksPositions.insert({ i,m_pBlocks[i]->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition() }); 
			}
		}
			
	}
}

void Environment::DeleteBlockFromGame(const int blockIndex)
{
	if (m_pBlocks[blockIndex]->GetComponent<BaseBlock>()->GetIsBreakable() && blockIndex != m_PushBlockIndex)
	{
		m_pBlocks[blockIndex]->GetComponent<GameEngine::AnimationComponent>()->SetIsDestroyed(true);
		m_BlockCollisionInfo.Detach(m_pBlocks[blockIndex]->GetComponent<BlockObserver>());
		m_pBlocks.erase(m_pBlocks.begin() + blockIndex);
		m_PushBlockIndex = -1;
		m_EnvEvent.CreateMessage({ Event::BlockIndexesChanged });
	}
}

void Environment::CheckEnemiesCollision()
{
	m_pEnemyManager->CheckEnemiesCollision(m_pBlocks, m_PushBlockIndex, &m_EnvEvent, &m_ScoreAppearingEvent, &m_AddingScoreInHUDEvent);
	m_pEnemyManager->HandleBorderCollision(m_pBorderBlock);
	m_pEnemyManager->CheckCollisionWithPlayer(m_pPlayer->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition(), &m_AddingScoreInHUDEvent);

}
