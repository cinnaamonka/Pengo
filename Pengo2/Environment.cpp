
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
	m_BorderLength(265),
	m_BorderHeight(305)
{
	GameEngine::GetVerticesFromJsonFile(filename, m_LevelVertices);

	int offset = 0;
	CreateBlocksCollection(m_LevelVertices, "DiamondBlock.tga", "diamond_block", offset, scene, BlocksTypes::Diamond);

	CreateBlocksCollection(m_LevelVertices, "EggsBlocks.tga", "egg_block", offset, scene, BlocksTypes::Eggs, 16);

	CreateBlocksCollection(m_LevelVertices, "EggsBlocks.tga", "ice_block", offset, scene, BlocksTypes::Breakable, 16);
	CreateBlocksCollection(m_LevelVertices, "EggsBlocks.tga", "enemy_block", offset, scene, BlocksTypes::BreaksOnSpot, 16);
	CreateBorder(scene, false, BlocksTypes::HorBorder);
	CreateBorder(scene, true, BlocksTypes::VerBorder);

	std::vector tempCollection = GameEngine::GetBlocksWithTag(m_LevelVertices, "borderCollider");

	std::unique_ptr<GameEngine::GameObject> borderCollider = std::make_unique<GameEngine::GameObject>();
	int left = static_cast<int>(tempCollection[0].block[0].x + m_BorderWidth);
	int bottom = static_cast<int>(tempCollection[0].block[0].y + m_BorderWidth);
	int width = m_BorderLength;
	int height = m_BorderHeight;
	borderCollider->AddComponent<GameEngine::BoxCollider>(left,bottom,width,height);
	borderCollider->AddComponent<BaseBlock>(50, BlocksTypes::HorBorder);
	borderCollider->AddComponent<CollisionComponent>();

	m_pBorderBlock = borderCollider.get();

	scene->Add(std::move(borderCollider));

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

	if (   m_pBorderBlock->GetComponent<CollisionComponent>()->IsBlockNearbyVertically(m_pPlayer, hitInfo)
		|| m_pBorderBlock->GetComponent<CollisionComponent>()->IsBlockNearbyHorizontally(m_pPlayer, hitInfo))
	{
		CheckBorderCollision(hitInfo);
	}
}

void Environment::CreateBlocksCollection(std::vector<GameEngine::Block> blocks, const std::string& name,
	const std::string& tag, int& offset, GameEngine::Scene* scene, BlocksTypes types, int clipTextureAmount)
{
	std::vector<GameEngine::Block> tempCollection = GameEngine::GetBlocksWithTag(m_LevelVertices, tag);

	for (int i = 0; i < static_cast<int>(tempCollection.size()); ++i)
	{
		auto block = BaseBlock::CreateBlock(tempCollection[i].block[0], name, i + offset, types, clipTextureAmount);

		if (tag == "ice_block" || tag == "egg_block" || tag == "enemy_block")
		{
			auto textureComponent = block->GetComponent<GameEngine::TextureComponent>();

			auto textureSizeX = textureComponent->GetTexture()->GetSize().x / textureComponent->GetTextureClipAmount();
			auto textureSizeY = textureComponent->GetTexture()->GetSize().y;

			block->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });
		}

		m_BlockCollisionInfo.Attach(block->GetComponent<BlockObserver>());

		m_pBlocks.push_back(block.get());

		if (block->GetComponent<BaseBlock>()->GetContainsEggs())
		{
			m_EggBlocksIndexes.push_back(i + offset);
		}

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
			m_EggBlocksIndexes.erase(std::remove(m_EggBlocksIndexes.begin(), m_EggBlocksIndexes.end(), index), m_EggBlocksIndexes.end());
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

void Environment::CreateBorder(GameEngine::Scene* scene, bool isVertical, BlocksTypes type)
{
	const std::string textureFile = isVertical ? "BorderV.tga" : "BorderH.tga";
	const auto& tempCollection = isVertical ? GameEngine::GetBlocksWithTag(m_LevelVertices, "verBorder") : GameEngine::GetBlocksWithTag(m_LevelVertices, "horBorder");

	for (const auto& blockData : tempCollection)
	{
		glm::vec3 position = isVertical
			? glm::vec3{ blockData.block[0].x, blockData.block[0].y, 0 }
		: glm::vec3{ blockData.block[0].x + m_BorderWidth, blockData.block[0].y + m_BorderWidth, 0 };
	
		int borderLength = isVertical ? m_BorderWidth : m_BorderLength;
		int borderHeight = isVertical ? m_BorderHeight : m_BorderWidth;

		auto borderBlock = BaseBlock::CreateBlock(blockData.block[0], textureFile, 50, type, 3, borderLength, borderHeight, position);

		auto textureComponent = borderBlock->GetComponent<GameEngine::TextureComponent>();
		auto texture = textureComponent->GetTexture();
		auto textureSizeX = isVertical ? (texture->GetSize().x / textureComponent->GetTextureClipAmount()) : texture->GetSize().x;
		auto textureSizeY = isVertical ? texture->GetSize().y : (texture->GetSize().y / textureComponent->GetTextureClipAmount());

		borderBlock->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0, textureSizeX, textureSizeY });

		m_pBorderBlocks.push_back(borderBlock.get());

		scene->Add(std::move(borderBlock));
	}
}

void Environment::CheckBorderCollision(const GameEngine::HitInfo& hitInfo)
{
	for (auto block : m_pBorderBlocks)
	{
		GameEngine::Rect rect = block->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

		if (GameEngine::IsPointInsideRect({ hitInfo.intersectPoint.x,hitInfo.intersectPoint.y,0 }, rect, 30.0f))
		{
			block->GetComponent<GameEngine::AnimationComponent>()->SetWasPushed(true);
			return;
		}
		else
		{
			block->GetComponent<GameEngine::AnimationComponent>()->SetWasPushed(false);
		}

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

void Environment::SpawnEnemyFromEggBlock()
{
	if (!m_EggBlocksIndexes.empty())
	{
		m_pBlocks[m_EggBlocksIndexes[0]]->GetComponent<GameEngine::AnimationComponent>()->SetIsDestroyed(true);
		m_pEnemyManager->SpawnEnemy(m_pBlocks[m_EggBlocksIndexes[0]]->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition(), m_pPlayer);
		m_BlockCollisionInfo.Detach(m_pBlocks[m_EggBlocksIndexes[0]]->GetComponent<BlockObserver>());
		m_pBlocks.erase(m_pBlocks.begin() + m_EggBlocksIndexes[0]);
		m_EggBlocksIndexes.erase(std::remove(m_EggBlocksIndexes.begin(), m_EggBlocksIndexes.end(), static_cast<int>(m_EggBlocksIndexes[0])), m_EggBlocksIndexes.end());
		m_PushBlockIndex = -1;
		m_EnvEvent.CreateMessage(Event::BlockIndexesChanged);
		m_AddingScoreInHUDEvent.CreateMessage(GameEngine::HUDEvent::AddSnoBeesLife);
	}
}

void Environment::SetBordersUntouched()
{
	for (auto block : m_pBorderBlocks)
	{
		block->GetComponent<GameEngine::AnimationComponent>()->SetWasPushed(false);
	}
}

void Environment::ResetBlocksIndexes()
{
	m_DiamondBlocksPositions.clear();
	m_EggBlocksIndexes.clear();

	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{
		if (!m_pBlocks[i]->IsDestroyed())
		{
			m_pBlocks[i]->GetComponent<BaseBlock>()->SetBlockIndex(i);

			if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetIsDiamondBlock())
			{
				m_DiamondBlocksPositions.insert({ i,m_pBlocks[i]->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition() });
			}
			if (m_pBlocks[i]->GetComponent<BaseBlock>()->GetContainsEggs())
			{
				m_EggBlocksIndexes.push_back(i);
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
