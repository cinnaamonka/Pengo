#include "Environment.h"
#include <TimeManager.h>
#include "BlockComponent.h"
#include <BoxColliderComponent.h>
#include <TransformComponent.h> 
#include <ActorComponent.h>
#include <SoundServiceLocator.h>
#include <memory>
#include <Helpers.h>

Environment::Environment(GameEngine::GameObject* pGameObject, const std::string& filename, GameEngine::Scene* scene) :
	BaseComponent(pGameObject),
	m_pPlayer(nullptr),
	m_PushDirection{},
	m_PushedBlockIndex{},
	m_BlockCanBePushed(false),
	m_BorderWidth(25),
	m_BorderLength(310),
	m_BorderHeight(355)
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
				m_pBlocks.push_back(iceBlock.get());
				scene->Add(std::move(iceBlock));
			}
	}
}
void Environment::CheckCollision(GameEngine::Rect& shape)
{
	if (m_pPlayer->GetComponent<GameEngine::ActorComponent>()->GetCollisionBeChecked())
	{
		GameEngine::HitInfo hitInfo{};

		for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
		{
			if (m_pBlocks[i]->GetComponent<BaseBlock>()->IsCollidingHorizontally(shape, hitInfo))
			{
				m_CollisionHitInfoChanged.CreateMessage(hitInfo);
				m_PushedBlockIndex = i;
				if (m_pBlocks[i]->GetComponent<BaseBlock>()->m_CollisionEvent !=
					BaseBlock::CollisionEvent::collidedHor)
				{
					m_PushDirection = { hitInfo.normal.x,0,0 };

					const auto& pushedBlock = m_pBlocks[m_PushedBlockIndex]->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

					bool isMovingRight = hitInfo.normal.x > 0;

					const GameEngine::Rect collingRect =
					{
						pushedBlock.left + (isMovingRight ? 10 : -10),
						pushedBlock.bottom,
						pushedBlock.width,
						pushedBlock.height
					};


					if (!m_pBorderBlock->GetComponent<BaseBlock>()->IsCollidingHorizontally(collingRect, hitInfo))
					{
						m_pBlocks[m_PushedBlockIndex]->GetComponent<BaseBlock>()->SetPushSpeed(10.0f);
					}
				}

				break;
			}

			if (m_pBlocks[i]->GetComponent<BaseBlock>()->IsCollidingVertically(shape, hitInfo))
			{
				m_CollisionHitInfoChanged.CreateMessage(hitInfo);
				m_PushedBlockIndex = i;
				if (m_pBlocks[i]->GetComponent<BaseBlock>()->m_CollisionEvent !=
					BaseBlock::CollisionEvent::collidedVer)
				{
					m_PushDirection = { 0,hitInfo.normal.y,0 };

					const auto& pushedBlock = m_pBlocks[m_PushedBlockIndex]->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

					bool isMovingTop = hitInfo.normal.y > 0;

					const GameEngine::Rect collingRect =
					{
						pushedBlock.left,
						pushedBlock.bottom + (isMovingTop ? 10 : -10),
						pushedBlock.width,
						pushedBlock.height
					};


					if (!m_pBorderBlock->GetComponent<BaseBlock>()->IsCollidingHorizontally(collingRect, hitInfo))
					{
						m_pBlocks[m_PushedBlockIndex]->GetComponent<BaseBlock>()->SetPushSpeed(10.0f);
					}
				}

				break;
			}
		}

		if (m_pBorderBlock->GetComponent<BaseBlock>()->IsCollidingHorizontally(shape, hitInfo))
		{
			m_CollisionHitInfoChanged.CreateMessage(hitInfo);
		}
		if (m_pBorderBlock->GetComponent<BaseBlock>()->IsCollidingVertically(shape, hitInfo))
		{
			m_CollisionHitInfoChanged.CreateMessage(hitInfo);
		}
		m_pPlayer->GetComponent<GameEngine::ActorComponent>()->SetCollisionCanBeChecked(false);

	}
}

void Environment::CheckBlocksCollision(GameEngine::GameObject* gameObject)
{
	GameEngine::HitInfo hitInfo{};
	auto test = gameObject->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

	for (int i = 0; i < static_cast<int>(m_pBlocks.size()); ++i)
	{
		if (m_pBlocks[i]->GetComponent<BaseBlock>()->IsCollidingHorizontally(test, hitInfo))
		{
			if (i != m_PushedBlockIndex)
			{
				m_BlockCanBePushed = false;
				m_pBlocks[m_PushedBlockIndex]->GetComponent<BaseBlock>()->SetPushSpeed(0);
				gameObject->GetComponent<BaseBlock>()->m_CollisionEvent = BaseBlock::CollisionEvent::collidedHor;
				m_pBlocks[m_PushedBlockIndex]->GetComponent<HitObserver>()->Notify(hitInfo);

				// test
				auto& soundSystem = GameEngine::SoundServiceLocator::GetSoundSystemInstance();
				soundSystem.Load("../Data/Sound/test.wav", 0);
				soundSystem.Play(0, 5.f);
				break;
			}

		}
		if (m_pBlocks[i]->GetComponent<BaseBlock>()->IsCollidingVertically(test, hitInfo))
		{
			if (i != m_PushedBlockIndex)
			{
				m_BlockCanBePushed = false;
				m_pBlocks[m_PushedBlockIndex]->GetComponent<BaseBlock>()->SetPushSpeed(0);
				gameObject->GetComponent<BaseBlock>()->m_CollisionEvent = BaseBlock::CollisionEvent::collidedVer;
				m_pBlocks[m_PushedBlockIndex]->GetComponent<HitObserver>()->Notify(hitInfo);
				break;
			}
		}
	}
	if (m_pBorderBlock->GetComponent<BaseBlock>()->IsCollidingHorizontally(test, hitInfo))
	{
		m_BlockCanBePushed = false;
		m_pBlocks[m_PushedBlockIndex]->GetComponent<BaseBlock>()->SetPushSpeed(0);
		gameObject->GetComponent<BaseBlock>()->m_CollisionEvent = BaseBlock::CollisionEvent::collidedHor;
		m_pBlocks[m_PushedBlockIndex]->GetComponent<HitObserver>()->Notify(hitInfo);
	}
	if (m_pBorderBlock->GetComponent<BaseBlock>()->IsCollidingVertically(test, hitInfo))
	{
		m_BlockCanBePushed = false;
		m_pBlocks[m_PushedBlockIndex]->GetComponent<BaseBlock>()->SetPushSpeed(0);
		gameObject->GetComponent<BaseBlock>()->m_CollisionEvent = BaseBlock::CollisionEvent::collidedVer;
		m_pBlocks[m_PushedBlockIndex]->GetComponent<HitObserver>()->Notify(hitInfo);
	}

}
void Environment::Update()
{
	CheckCollision(m_pPlayer->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider());

	if (m_BlockCanBePushed)
	{
		CheckBlocksCollision(m_pBlocks[m_PushedBlockIndex]);
		m_pBlocks[m_PushedBlockIndex]->GetComponent<BaseBlock>()->PushBlock(m_PushDirection);
	}
}

void Environment::PushBlock()
{
	if (m_pBlocks[m_PushedBlockIndex]->GetComponent<BaseBlock>()->GetPushSpeed() != 0)
	{
		m_BlockCanBePushed = true;
	}
}

