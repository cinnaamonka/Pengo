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
	m_PushDirection{},
	m_BlockCanBePushed(false),
	m_BorderWidth(10),
	m_BorderLength(260),
	m_BorderHeight(300),
	m_PushedBlockIndex{}
{
	GameEngine::GetVerticesFromJsonFile(filename, m_VerticesIceBlocks, m_VerticesDiamondBlocks, m_BorderVertices);

	auto borderBlock = BaseBlock::CreateBlock(m_BorderVertices[0][0], "Border.tga",
		m_BorderLength, m_BorderHeight,
		glm::vec3{ m_BorderVertices[0][0].x + m_BorderWidth,m_BorderVertices[0][0].y + m_BorderWidth,0 });

	borderBlock->SetParent(GetGameObject());

	m_pBorderBlock = borderBlock.get();
	scene->Add(std::move(borderBlock));

	int amountOfIceBlocks = static_cast<int>(m_VerticesIceBlocks.size());
	int amountOfDiamondBlocks = static_cast<int>(m_VerticesDiamondBlocks.size());

	for (int i = 0; i < amountOfDiamondBlocks; ++i)
	{
		auto diamondBlock = BaseBlock::CreateBlock(m_VerticesDiamondBlocks[i][0], "DiamondBlock.tga");

		m_pBlocks.push_back(diamondBlock.get());
		diamondBlock->SetParent(GetGameObject());

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
				m_BlocksLifeStateChanged.Attach(iceBlock->GetComponent<GameEngine::LifetimeObserver>());
				iceBlock->SetParent(GetGameObject());
				m_pBlocks.push_back(iceBlock.get());
				scene->Add(std::move(iceBlock));
			}
	}
}
void Environment::CheckCollision()
{
	GameEngine::HitInfo blockCollisionInfo{};

	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{
		const bool isColliding = m_pBlocks[i]->GetComponent<CollisionComponent>()->IsColliding(m_pPlayer, blockCollisionInfo);

		if (isColliding)
		{
			m_CollisionHitInfoChanged.CreateMessage(blockCollisionInfo);
			m_PushDirection = { blockCollisionInfo.normal.x,blockCollisionInfo.normal.y, 0 };
			m_PushedBlockIndex = i;

			break;
		}
	}

	GameEngine::HitInfo borderCollisionInfo{};;

	const auto& shape = m_pPlayer->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

	if (m_pBorderBlock->GetComponent<BaseBlock>()->IsColliding(shape, borderCollisionInfo))
	{
		m_CollisionHitInfoChanged.CreateMessage(borderCollisionInfo);

	}

	m_pPlayer->GetComponent<GameEngine::ActorComponent>()->SetCollisionCanBeChecked(false);

	m_WasBlockPushed = false;
}

void Environment::HandleBlockCollision(GameEngine::GameObject* pushedBlock)
{
	GameEngine::HitInfo hitInfo{};

	auto& pushedBlockCollider = pushedBlock->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{
		if (i != m_PushedBlockIndex)
		{
			if (m_pBlocks[i]->GetComponent<CollisionComponent>()->IsBlockColliding(pushedBlock))
			{
				m_BlockCanBePushed = false;
				break;
			}
		}
	}

	if (m_pBorderBlock->GetComponent<BaseBlock>()->IsColliding(pushedBlockCollider, hitInfo))
	{
		m_BlockCanBePushed = false;
		pushedBlock->GetComponent<HitObserver>()->Notify(hitInfo);
	}
}
void Environment::Update()
{
	CheckCollision();

	if (m_BlockCanBePushed)
	{
		m_pBlocks[m_PushedBlockIndex]->GetComponent<BaseBlock>()->SetPushSpeed(5);

		m_pBlocks[m_PushedBlockIndex]->GetComponent<BaseBlock>()->PushBlock(m_PushDirection);

		HandleBlockCollision(m_pBlocks[m_PushedBlockIndex]);
	}
}

void Environment::PushBlock()
{
	m_WasBlockPushed = true;

	if (m_pBlocks[m_PushedBlockIndex] && m_pBlocks[m_PushedBlockIndex]->HasComponent<BaseBlock>())
	{
		m_BlockCanBePushed = true;
	}
}

