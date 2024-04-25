#include "HitObserver.h"
#include <ActorComponent.h>
#include <BoxColliderComponent.h>
#include <TransformComponent.h>
#include "BaseBlock.h"

HitObserver::HitObserver(GameEngine::GameObject* pGameObject) :
	BaseComponent(pGameObject)
{
}

void HitObserver::ResetHorizontalPosition(const GameEngine::Rect& actorShape, const GameEngine::HitInfo& hitInfo)
{
	GameEngine::Rect tempRect{ actorShape };

	float left = static_cast<float>(actorShape.left);

	float intersectX = static_cast<float>(hitInfo.intersectPoint.x);

	if (intersectX < left + actorShape.width / 2)
	{
		int roundedIntersectX = static_cast<int>((intersectX + 10.0f) / 20.0f) * 20;
		tempRect.left = roundedIntersectX + 1;
	}
	else if (intersectX > left + actorShape.width / 2)
	{
		int roundedIntersectX = static_cast<int>(intersectX - actorShape.height);
		roundedIntersectX -= roundedIntersectX % 20;
		tempRect.left = roundedIntersectX - 1;
	}

	GetGameObject()->GetComponent<GameEngine::TransformComponent>()->SetLocalPosition(glm::vec3{ tempRect.left,tempRect.bottom,0 });
}

void HitObserver::ResetVerticalPosition(const GameEngine::Rect& actorShape, const GameEngine::HitInfo& hitInfo)
{
	GameEngine::Rect tempRect{ actorShape };

	float bottom = static_cast<float>(actorShape.bottom);

	float intersectY = static_cast<float>(hitInfo.intersectPoint.y);

	if (intersectY < bottom + actorShape.height / 2)
	{
		int roundedIntersectY = static_cast<int>((intersectY + 10.0f) / 20.0f) * 20;
		tempRect.bottom = roundedIntersectY + 1;
	}
	else if (intersectY > bottom + actorShape.height / 2)
	{
		int roundedIntersectY = static_cast<int>(intersectY - actorShape.height);
		roundedIntersectY -= roundedIntersectY % 20;
		tempRect.bottom = roundedIntersectY - 1;
	}

	GetGameObject()->GetComponent<GameEngine::TransformComponent>()->SetLocalPosition(glm::vec3{ tempRect.left,tempRect.bottom,0 });
}
void HitObserver::Notify(const GameEngine::HitInfo& message_from_subject)
{
	//vertical 
	if (glm::abs(message_from_subject.normal.y) > 0.9f && glm::abs(message_from_subject.normal.x) < 0.1f)
	{
		const auto& shape = GetGameObject()->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

		GameEngine::Rect shapeCopy
		{
			shape.left,
			shape.bottom,
			shape.width,
			shape.height

		};
		ResetVerticalPosition(shapeCopy, message_from_subject);
	}
	//horizontal
	else if (glm::abs(message_from_subject.normal.x) > 0.9f && glm::abs(message_from_subject.normal.y) < 0.1f)
	{
		const auto& shape = GetGameObject()->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider();

		GameEngine::Rect shapeCopy
		{
			shape.left,
			shape.bottom,
			shape.width,
			shape.height

		};

		ResetHorizontalPosition(shapeCopy, message_from_subject);
	}

}

