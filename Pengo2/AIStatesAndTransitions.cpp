#include "AIStatesAndTransitions.h"
#include <AnimationComponent.h>

void PatrolState::OnEnter(GameEngine::AnimationComponent*)
{

}

void PatrolState::OnExit(GameEngine::AnimationComponent*)
{
}

void PatrolState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	glm::vec3 pos = pAnimationComponent->GetPos();

	glm::vec3 direction = pAnimationComponent->GetMovementDirection();

	float speed = pAnimationComponent->GetSpeed();

	if (direction.x != 0)
	{
		pos.x += speed * direction.x;
	}
	if (direction.y != 0)
	{
		pos.y += speed * direction.y;
	}
	pAnimationComponent->SetPos(pos);
}

void ChaseState::OnEnter(GameEngine::AnimationComponent*)
{
}

void ChaseState::OnExit(GameEngine::AnimationComponent*)
{
}

void ChaseState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	glm::vec3 pos = pAnimationComponent->GetPos();

	glm::vec3 direction = pAnimationComponent->GetMovementDirection();

	float speed = pAnimationComponent->GetSpeed();

	if (direction.x != 0)
	{
		pos.x += speed * direction.x;
	}
	if (direction.y != 0)
	{
		pos.y += speed * direction.y;
	}

	pAnimationComponent->SetPos(pos);
}

bool HasNoticedActor::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	bool isChasing = pAnimationComponent->GetIsChasing();

	return isChasing;
}
