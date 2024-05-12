#include "EnemyAnimationStates.h"
#include <Helpers.h>
#include <BlackboardComponent.h>

void EnemyPatrolState::HandleInput(GameEngine::GameObject* object)
{
	GameEngine::BlackboardComponent* blackboardComponent = object->GetComponent<GameEngine::BlackboardComponent>();

	glm::vec3 movementDirection;
	blackboardComponent->GetData("MovementDirection", movementDirection);

	blackboardComponent->ChangeData("HorizontalOffset", 0);

	blackboardComponent->ChangeData("NumberOfFrames", 2);
	blackboardComponent->ChangeData("VerticalOffset", 1);

}

void EnemyPatrolState::Update(GameEngine::GameObject* object)
{
	GameEngine::BlackboardComponent* blackboardComponent = object->GetComponent<GameEngine::BlackboardComponent>();

	GameEngine::AnimationUpdate(blackboardComponent);
}

void EnemyDyingState::HandleInput(GameEngine::GameObject* object)
{
	GameEngine::BlackboardComponent* blackboardComponent = object->GetComponent<GameEngine::BlackboardComponent>();

	glm::vec3 movementDirection;
	blackboardComponent->GetData("MovementDirection", movementDirection);

	if (movementDirection.x != 0)
	{
		blackboardComponent->ChangeData("HorizontalOffset", 2);
	}
	if (movementDirection.y > 0)
	{
		blackboardComponent->ChangeData("HorizontalOffset", 0);
	}
	if (movementDirection.y < 0)
	{
		blackboardComponent->ChangeData("HorizontalOffset", 4);
	}
	blackboardComponent->ChangeData("NumberOfFrames", 2);
	blackboardComponent->ChangeData("VerticalOffset", 4);
	blackboardComponent->ChangeData("FramesPerSec", 1);
}

void EnemyDyingState::Update(GameEngine::GameObject* object)
{
	GameEngine::BlackboardComponent* blackboardComponent = object->GetComponent<GameEngine::BlackboardComponent>();

	GameEngine::AnimationUpdate(blackboardComponent);

	int currentAnimationFrame;
	blackboardComponent->GetData("AnimationFrame", currentAnimationFrame);

	int numberOfFrames;
	blackboardComponent->GetData("NumberOfFrames", numberOfFrames); 

	if (currentAnimationFrame == numberOfFrames - 1) 
	{
		blackboardComponent->Destroy(); 
	}
}
