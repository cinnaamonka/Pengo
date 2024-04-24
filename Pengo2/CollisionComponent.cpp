#include "CollisionComponent.h"
#include "BaseBlock.h"
#include <GameObject.h>

CollisionComponent::CollisionComponent(GameEngine::GameObject* pGameObject) :
	BaseComponent(pGameObject),
	m_Pushed(false)
{

}

void CollisionComponent::HandleCollision(GameEngine::Rect& shape, GameEngine::GameObject* border,
	glm::vec3& pushDirection, GameEngine::GameObject* pushedBlock, GameEngine::HitInfo& hitInfo)
{
	GameEngine::HitInfo test{};

	if (GetGameObject()->GetComponent<BaseBlock>()->IsCollidingHorizontally(shape, hitInfo))
	{
		test.normal = hitInfo.normal;
		test.intersectPoint = hitInfo.intersectPoint;

		if (m_CollisionEvent != CollisionEvent::CollidedHor)
		{
			pushDirection = { hitInfo.normal.x,0,0 };

			const auto& pushedBlockCollider = pushedBlock->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

			bool isMovingRight = hitInfo.normal.x > 0;

			const GameEngine::Rect collingRect =
			{
				pushedBlockCollider.left + (isMovingRight ? 10 : -10),
				pushedBlockCollider.bottom,
				pushedBlockCollider.width,
				pushedBlockCollider.height
			};


			if (!border->GetComponent<BaseBlock>()->IsCollidingHorizontally(collingRect, hitInfo))
			{
				pushedBlock->GetComponent<BaseBlock>()->SetPushSpeed(10.0f);
			}

		}
		m_HasCollided = true;
		hitInfo.normal = test.normal;
		hitInfo.intersectPoint = test.intersectPoint;

		return;
	}
	else
	{
		hitInfo.normal = test.normal;
		hitInfo.intersectPoint = test.intersectPoint;
		m_HasCollided = false;
	}

	if (GetGameObject()->GetComponent<BaseBlock>()->IsCollidingVertically(shape, hitInfo))
	{
		test.normal = hitInfo.normal;
		test.intersectPoint = hitInfo.intersectPoint;

		if (m_CollisionEvent != CollisionEvent::CollidedVer)
		{
			pushDirection = { 0,hitInfo.normal.y,0 };

			const auto& pushedBlockCollider = pushedBlock->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

			bool isMovingTop = hitInfo.normal.y > 0;

			const GameEngine::Rect collingRect =
			{
				pushedBlockCollider.left,
				pushedBlockCollider.bottom + (isMovingTop ? 10 : -10),
				pushedBlockCollider.width,
				pushedBlockCollider.height
			};


			if (!border->GetComponent<BaseBlock>()->IsCollidingVertically(collingRect, hitInfo))
			{
				pushedBlock->GetComponent<BaseBlock>()->SetPushSpeed(10.0f);
			}
		
		}
		m_HasCollided = true;
		hitInfo.normal = test.normal;
		hitInfo.intersectPoint = test.intersectPoint;
		return;
	}
	else
	{
		hitInfo.normal = test.normal;
		hitInfo.intersectPoint = test.intersectPoint;
		m_HasCollided = false;
	}

}

void CollisionComponent::HandleBlocksCollision(GameEngine::GameObject* gameObject, bool& blockCanBePushed)
{
	GameEngine::HitInfo hitInfo{};

	GameEngine::Rect boxCollider = gameObject->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

	if (GetGameObject()->GetComponent<BaseBlock>()->IsCollidingHorizontally(boxCollider, hitInfo))
	{
		blockCanBePushed = false;

		gameObject->GetComponent<BaseBlock>()->SetPushSpeed(0);
		gameObject->GetComponent<CollisionComponent>()->m_CollisionEvent = CollisionEvent::CollidedHor;
		gameObject->GetComponent<HitObserver>()->Notify(hitInfo);
		m_HasCollided = true;
		return;
	}
	else
	{
		m_HasCollided = false;
	}
	if (GetGameObject()->GetComponent<BaseBlock>()->IsCollidingVertically(boxCollider, hitInfo))
	{
	
		blockCanBePushed = false;

		gameObject->GetComponent<BaseBlock>()->SetPushSpeed(0);
		gameObject->GetComponent<CollisionComponent>()->m_CollisionEvent = CollisionEvent::CollidedVer;
		gameObject->GetComponent<HitObserver>()->Notify(hitInfo);
		m_HasCollided = true;
		return;

	}
	else
	{
		m_HasCollided = false;
	}

}
