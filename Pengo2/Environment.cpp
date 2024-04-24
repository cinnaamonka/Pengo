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

Environment::Environment(GameEngine::GameObject* pGameObject, const std::string& filename, GameEngine::Scene* scene) :
	BaseComponent(pGameObject),
	m_pPlayer(nullptr),
	m_PushDirection{},
	m_BlockCanBePushed(false),
	m_BorderWidth(25),
	m_BorderLength(310),
	m_BorderHeight(355),
	m_PushedBlockIndex{}
{
	GameEngine::GetVerticesFromJsonFile(filename, m_VerticesIceBlocks, m_VerticesDiamondBlocks, m_BorderVertices);

	auto borderBlock = BaseBlock::CreateBlock(m_BorderVertices[0][0], "Border.tga",
		m_BorderLength, m_BorderHeight,
		glm::vec3{ m_BorderVertices[0][0].x + m_BorderWidth,m_BorderVertices[0][0].y + m_BorderWidth,0 });

	m_pBorderBlock = borderBlock.get();
	scene->Add(std::move(borderBlock));

	int amountOfIceBlocks = static_cast<int>(m_VerticesIceBlocks.size());
	int amountOfDiamondBlocks = static_cast<int>(m_VerticesDiamondBlocks.size());

	for (int i = 0; i < amountOfDiamondBlocks; ++i)
	{
		auto diamondBlock = BaseBlock::CreateBlock(m_VerticesDiamondBlocks[i][0], "DiamondBlock.tga");

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
				auto iceBlock = BaseBlock::CreateBlock(position, "IceBlock.tga");
				auto textureSizeX = iceBlock->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / 10;
				auto textureSizeY = iceBlock->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y;

				iceBlock->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });
				m_pBlocks.push_back(iceBlock.get());
				scene->Add(std::move(iceBlock));
			}
	}
}
void Environment::CheckCollision()
{
	if (m_pPlayer->GetComponent<GameEngine::ActorComponent>()->GetCollisionBeChecked())
	{
		GameEngine::HitInfo hitInfo{};

		for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
		{
			m_pBlocks[i]->GetComponent<CollisionComponent>()->HandleCollision(m_pPlayer, m_pBorderBlock, m_PushDirection,
				m_pBlocks[m_PushedBlockIndex], hitInfo, m_test);

			if (m_pBlocks[i]->GetComponent<CollisionComponent>()->GetHasCollided())
			{
				m_CollisionHitInfoChanged.CreateMessage(hitInfo);
				m_PushedBlockIndex = i;
				break;
			}
		}

		auto shape = m_pPlayer->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

		if (m_pBorderBlock->GetComponent<BaseBlock>()->IsCollidingHorizontally(shape, hitInfo))
		{
			m_CollisionHitInfoChanged.CreateMessage(hitInfo);

		}
		if (m_pBorderBlock->GetComponent<BaseBlock>()->IsCollidingVertically(shape, hitInfo))
		{
			m_CollisionHitInfoChanged.CreateMessage(hitInfo);
		}

	}
	m_pPlayer->GetComponent<GameEngine::ActorComponent>()->SetCollisionCanBeChecked(false);
	m_test = false;
}

void Environment::CheckBlocksCollision(GameEngine::GameObject* gameObject)
{
	GameEngine::HitInfo hitInfo{};
	auto test = gameObject->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{
		if (i != m_PushedBlockIndex)
		{
			m_pBlocks[i]->GetComponent<CollisionComponent>()->HandleBlocksCollision(gameObject);

			if (m_pBlocks[i]->GetComponent<CollisionComponent>()->GetHasCollided())
			{
				m_BlockCanBePushed = false;
				break;
			}
		}

	}
	if (m_pBorderBlock->GetComponent<BaseBlock>()->IsCollidingHorizontally(test, hitInfo))
	{
		m_BlockCanBePushed = false;
		gameObject->GetComponent<BaseBlock>()->SetPushSpeed(0);
		gameObject->GetComponent<CollisionComponent>()->m_CollisionEvent = CollisionComponent::CollisionEvent::CollidedHor;
		gameObject->GetComponent<HitObserver>()->Notify(hitInfo);
	}
	if (m_pBorderBlock->GetComponent<BaseBlock>()->IsCollidingVertically(test, hitInfo))
	{
		m_BlockCanBePushed = false;
		gameObject->GetComponent<BaseBlock>()->SetPushSpeed(0);
		gameObject->GetComponent<CollisionComponent>()->m_CollisionEvent = CollisionComponent::CollisionEvent::CollidedVer;
		gameObject->GetComponent<HitObserver>()->Notify(hitInfo);
	}

}
void Environment::Update()
{
	CheckCollision();

	if (m_BlockCanBePushed)
	{
		CheckBlocksCollision(m_pBlocks[m_PushedBlockIndex]);
		m_pBlocks[m_PushedBlockIndex]->GetComponent<BaseBlock>()->PushBlock(m_PushDirection);
	}
}

void Environment::PushBlock()
{
	m_test = true;

	if (m_pBlocks[m_PushedBlockIndex]->GetComponent<BaseBlock>()->GetPushSpeed() != 0)
	{
		m_BlockCanBePushed = true;
	}

}

