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
void CollisionComponent::ResetHorizontalPosition(const GameEngine::Rect& actorShape, const GameEngine::HitInfo& hitInfo)
{
	GameEngine::Rect tempRect{ actorShape };

	float left = static_cast<float>(actorShape.left);

	float intersectX = static_cast<float>(hitInfo.intersectPoint.x);

	if (intersectX < left + actorShape.width / 2)
	{
		tempRect.left = static_cast<int>(intersectX + m_BottomOffset);
	}
	else if (intersectX > left + actorShape.width / 2)
	{
		tempRect.left = static_cast<int>(intersectX - actorShape.width - m_BottomOffset);
	}

	GetGameObject()->GetComponent<GameEngine::TransformComponent>()->SetLocalPosition(glm::vec3{ tempRect.left,tempRect.bottom,0 });
}

void CollisionComponent::ResetVerticalPosition(const GameEngine::Rect& actorShape, const GameEngine::HitInfo& hitInfo)
{
	GameEngine::Rect tempRect{ actorShape };

	float bottom = static_cast<float>(actorShape.bottom);

	float intersectY = static_cast<float>(hitInfo.intersectPoint.y);

	if (intersectY < bottom + actorShape.height / 2)
	{
		tempRect.bottom = static_cast<int>(intersectY + m_BottomOffset);
	}
	else if (intersectY > bottom + actorShape.height / 2)
	{
		tempRect.bottom = static_cast<int>(intersectY - actorShape.height - m_BottomOffset);
	}
	GetGameObject()->GetComponent<GameEngine::TransformComponent>()->SetLocalPosition(glm::vec3{ tempRect.left,tempRect.bottom,0 });
}
void CollisionComponent::HandleHitEvent(const GameEngine::HitInfo& hitInfo)
{
	//vertical 
	if (glm::abs(hitInfo.normal.y) > m_TopOffset && glm::abs(hitInfo.normal.x) < m_BottomOffset)
	{
		const auto& shape = GetGameObject()->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

		GameEngine::Rect shapeCopy
		{
			shape.left,
			shape.bottom,
			shape.width,
			shape.height

		};
		ResetVerticalPosition(shapeCopy, hitInfo);
	}
	//horizontal
	else if (glm::abs(hitInfo.normal.x) > m_TopOffset && glm::abs(hitInfo.normal.y) < m_BottomOffset)
	{
		const auto& shape = GetGameObject()->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

		GameEngine::Rect shapeCopy
		{
			shape.left,
			shape.bottom,
			shape.width,
			shape.height

		};

		ResetHorizontalPosition(shapeCopy, hitInfo);
	}

}
