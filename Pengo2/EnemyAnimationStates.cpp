#include "EnemyAnimationStates.h"
#include <Helpers.h>
#include <AnimationComponent.h>

void EnemyPatrolState::HandleInput(GameEngine::GameObject* object)
{
	GameEngine::AnimationComponent* animationComponent = object->GetComponent<GameEngine::AnimationComponent>();

	animationComponent->SetHorizontalOffset(m_HorizontalOffset);

	animationComponent->SetNumberOfFrames(m_NumberOfEnterStateFrames);
	animationComponent->SetVerticalOffset(m_VerticalOffset);

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

	if (movementDirection.x > 0)
	{
		animationComponent->SetHorizontalOffset(m_HorizontalDeathOffset);
	}
	if (movementDirection.x < 0)
	{
		animationComponent->SetHorizontalOffset(m_HorizontalDeathOffset);
	}
	if (movementDirection.y > 0)
	{
		animationComponent->SetHorizontalOffset(m_VerticalTopDeathOffset);
	}
	if (movementDirection.y < 0)
	{
		animationComponent->SetHorizontalOffset(m_VerticalBottomDeathOffset);
	}

	animationComponent->SetNumberOfFrames(m_NumberOfEnterStateFrames);
	animationComponent->SetVerticalOffset(m_VerticalOffset);
	animationComponent->SetFramesPerSec(m_FramesPerSec);
	animationComponent->SetAnimationTime(0.0f);
	animationComponent->SetAnimationFrame(0);
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
