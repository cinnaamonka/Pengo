#include "CollisionComponent.h"
#include "BaseBlock.h"
#include <GameObject.h>

CollisionComponent::CollisionComponent(GameEngine::GameObject* pGameObject) :
	BaseComponent(pGameObject)
{

}

bool CollisionComponent::IsColliding(GameEngine::GameObject* actor, GameEngine::HitInfo& hitInfo) const
{
	const auto& boxCollider = actor->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

	return GetGameObject()->GetComponent<BaseBlock>()->IsCollidingVertically(boxCollider, hitInfo) ||
		GetGameObject()->GetComponent<BaseBlock>()->IsCollidingHorizontally(boxCollider, hitInfo);
}

bool CollisionComponent::IsBlockNearbyHorizontally(GameEngine::GameObject* actor, GameEngine::HitInfo& hitInfo) const
{

	glm::vec3 direction = actor->GetComponent<GameEngine::AnimationComponent>()->GetMovementDirection();

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
	else if (direction.y == 0)
	{
		increasedRect.left -= offset;
		increasedRect.width += 2 * offset;
	}

	return GetGameObject()->GetComponent<BaseBlock>()->IsCollidingHorizontally(increasedRect, hitInfo);
	
}

bool CollisionComponent::IsBlockNearbyVertically(GameEngine::GameObject* actor, GameEngine::HitInfo& hitInfo) const
{

	glm::vec3 direction = actor->GetComponent<GameEngine::AnimationComponent>()->GetMovementDirection();

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
	else if(direction.x == 0)
	{
		increasedRect.bottom -= offset;
		increasedRect.height += 2 * offset;
	}
	
	return GetGameObject()->GetComponent<BaseBlock>()->IsCollidingVertically(increasedRect, hitInfo);
	
}
