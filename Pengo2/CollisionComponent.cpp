#include "CollisionComponent.h"
#include "BaseBlock.h"
#include <GameObject.h>
#include "BlackboardComponent.h"

CollisionComponent::CollisionComponent(GameEngine::GameObject* pGameObject) :
	BaseComponent(pGameObject)
{
}

bool CollisionComponent::IsColliding(GameEngine::GameObject* actor, GameEngine::HitInfo& hitInfo)
{
	const auto& actorColliderBox = actor->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

	if (!GetGameObject()->GetComponent<BaseBlock>()->IsColliding(actorColliderBox, hitInfo)) { return false; }

	GameEngine::HitInfo collideInforamtion{};

	collideInforamtion.normal = hitInfo.normal;

	return true;
}

bool CollisionComponent::IsBlockColliding(GameEngine::GameObject* pushedBlock)
{
	GameEngine::HitInfo hitInfo{};

	GameEngine::Rect boxCollider = pushedBlock->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

	if (!GetGameObject()->GetComponent<BaseBlock>()->IsColliding(boxCollider, hitInfo)) { return false; }

	pushedBlock->GetComponent<HitObserver>()->Notify(hitInfo);

	return true;
}
