#include "EnemyAnimationStates.h"
#include <Helpers.h>
#include <AnimationComponent.h>

void EnemyPatrolState::HandleInput(GameEngine::GameObject* object)
{
	GameEngine::AnimationComponent* animationComponent = object->GetComponent<GameEngine::AnimationComponent>();

	animationComponent->SetHorizontalOffset(0);

	animationComponent->SetNumberOfFrames(2);
	animationComponent->SetVerticalOffset(1);

}

void EnemyPatrolState::Update(GameEngine::GameObject* object)
{
	GameEngine::AnimationComponent* animationComponent = object->GetComponent<GameEngine::AnimationComponent>();

	GameEngine::AnimationUpdate(animationComponent);
}

void EnemyDyingState::HandleInput(GameEngine::GameObject* object)
{
	GameEngine::AnimationComponent* animationComponent = object->GetComponent<GameEngine::AnimationComponent>();

	glm::vec3 movementDirection = animationComponent->GetMovementDirection();

	if (movementDirection.x != 0)
	{
		animationComponent->SetHorizontalOffset(2);
	}
	if (movementDirection.y > 0)
	{
		animationComponent->SetHorizontalOffset(0);
	}
	if (movementDirection.y < 0)
	{
		animationComponent->SetHorizontalOffset(4);
	}

	animationComponent->SetNumberOfFrames(2);
	animationComponent->SetVerticalOffset(4);
	animationComponent->SetFramesPerSec(1);
}

void EnemyDyingState::Update(GameEngine::GameObject* object)
{
	GameEngine::AnimationComponent* animationComponent = object->GetComponent<GameEngine::AnimationComponent>();

	GameEngine::AnimationUpdate(animationComponent);

	int currentAnimationFrame = animationComponent->GetAnimationFrame();

	int numberOfFrames = animationComponent->GetNumberOfFrames();

	if (currentAnimationFrame == numberOfFrames - 1)
	{
		animationComponent->Destroy();
	}
}
