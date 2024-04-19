#include "HitObserver.h"
#include <ActorComponent.h>
#include <BoxColliderComponent.h>
#include <TransformComponent.h>

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
		tempRect.left = static_cast<int>(intersectX);
	}
	else if (intersectX > left + actorShape.width / 2)
	{
		tempRect.left = static_cast<int>(intersectX - actorShape.width);
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
		tempRect.bottom = static_cast<int>(intersectY);
	}
	else if (intersectY > bottom + actorShape.height / 2)
	{
		tempRect.bottom = static_cast<int>(intersectY - actorShape.height);
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

