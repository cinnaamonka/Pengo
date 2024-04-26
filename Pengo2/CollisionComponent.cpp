#include "CollisionComponent.h"
#include "BaseBlock.h"
#include <GameObject.h>
#include <FSM.h>
#include "BlackboardComponent.h"
#include "ActorComponent.h"

CollisionComponent::CollisionComponent(GameEngine::GameObject* pGameObject) :
	BaseComponent(pGameObject),
	m_Pushed(false)
{
}

bool CollisionComponent::IsColliding(GameEngine::GameObject* actor, GameEngine::HitInfo& hitInfo)
{
	if (!this) return false;
	if (actor->IsDestroyed()) return false;

	const auto& boxCollider = actor->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

	if (GetGameObject()->GetComponent<BaseBlock>()->IsCollidingVertically(boxCollider, hitInfo))
	{
		return true;
	}
	if (GetGameObject()->GetComponent<BaseBlock>()->IsCollidingHorizontally(boxCollider, hitInfo)) 
	{
		return true;
	}
	return false;
}

bool CollisionComponent::IsBlockNearbyHorizontally(GameEngine::GameObject* actor, GameEngine::HitInfo& hitInfo)
{
	if (!this) return false;
	if (actor->IsDestroyed()) return false;

	glm::vec3 direction{};
	actor->GetComponent<GameEngine::FSM>()->GetBlackboard()->GetData("MovementDirection", direction);

	const auto& currentActorShape = actor->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

	const int offset = 10;
	GameEngine::Rect increasedRect = currentActorShape;

	if (direction.x == -1)
	{
		increasedRect.left -= offset;
	}
	else if (direction.x == 1)
	{
		increasedRect.width += offset;
	}
	else
	{
		increasedRect.left -= offset;
		increasedRect.width += 2 * offset;
	}

	if (GetGameObject()->GetComponent<BaseBlock>()->IsCollidingHorizontally(increasedRect, hitInfo))
	{
		return true;
	}
	return false;
}

bool CollisionComponent::IsBlockNearbyVertically(GameEngine::GameObject* actor, GameEngine::HitInfo& hitInfo)
{
	if (!this) return false;
	if (actor->IsDestroyed()) return false;

	glm::vec3 direction{};
	actor->GetComponent<GameEngine::FSM>()->GetBlackboard()->GetData("MovementDirection", direction);

	const auto& currentActorShape = actor->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

	const int offset = 10;
	GameEngine::Rect increasedRect = currentActorShape;

	if (direction.y == -1)
	{
		increasedRect.bottom -= offset;
	}
	else if (direction.y == 1)
	{
		increasedRect.height += offset;
	}
	else
	{
		increasedRect.bottom -= offset;
		increasedRect.height += 2 * offset;
	}
	
	if (GetGameObject()->GetComponent<BaseBlock>()->IsCollidingVertically(increasedRect, hitInfo))
	{
		return true;
	}
	return false;
}
