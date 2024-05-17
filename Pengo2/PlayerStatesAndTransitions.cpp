#include "PlayerStatesAndTransitions.h"
#include <AnimationComponent.h>

void IdleState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(1);
	pAnimationComponent->SetHorizontalOffset(0);
	pAnimationComponent->SetVerticalOffset(0);
}

void IdleState::OnExit(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetWasInputGiven(false);
}

void IdleState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	AnimationUpdate(pAnimationComponent);
}

void RunningState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	glm::vec3 movementDirection = pAnimationComponent->GetMovementDirection();

	if (movementDirection.x != 0)
	{
		pAnimationComponent->SetHorizontalOffset(2);
	}
	else if (movementDirection.y < 0)
	{
		pAnimationComponent->SetHorizontalOffset(4);
	}
	else if (movementDirection.y > 0)
	{
		pAnimationComponent->SetHorizontalOffset(0);
	}
	pAnimationComponent->SetNumberOfFrames(2);
	pAnimationComponent->SetVerticalOffset(0);
}

void RunningState::OnExit(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetWasInputGiven(false);
}

void RunningState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	AnimationUpdate(pAnimationComponent);

	pAnimationComponent->SetWasInputGiven(false);
}

void PushingState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	glm::vec3 movementDirection = pAnimationComponent->GetMovementDirection();

	if (movementDirection.x > 0 || movementDirection.x < 0)
	{
		pAnimationComponent->SetHorizontalOffset(2);
	}
	else if (movementDirection.y < 0)
	{
		pAnimationComponent->SetHorizontalOffset(4);
	}
	else if (movementDirection.y > 0)
	{
		pAnimationComponent->SetHorizontalOffset(4);
	}
	pAnimationComponent->SetNumberOfFrames(2); 
	pAnimationComponent->SetVerticalOffset(1); 
}
void PushingState::OnExit(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetWasPushed(false);
	pAnimationComponent->SetWasInputGiven(false);
}
void PushingState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	AnimationUpdate(pAnimationComponent);  
	pAnimationComponent->SetWasPushed(false);
}

void PlayerDyingState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetHorizontalOffset(0);
	pAnimationComponent->SetVerticalOffset(2);
	pAnimationComponent->SetNumberOfFrames(2);
}


void PlayerDyingState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	AnimationUpdate(pAnimationComponent); 
}

bool IsInputGiven::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	bool inputWasGiven = pAnimationComponent->GetWasInputGiven();

	return inputWasGiven;
}

bool IsInputNotGiven::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	bool inputWasGiven = pAnimationComponent->GetWasInputGiven();

	return !inputWasGiven;
}
bool IsBlockPushed::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	bool wasBlockPushed = pAnimationComponent->GetWasPushed();

	return wasBlockPushed;
}
bool IsBlockNotPushed::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	bool wasBlockPushed = pAnimationComponent->GetWasPushed();
	 
	float animTime = pAnimationComponent->GetAnimationTime();

	if (animTime <= 1.f && wasBlockPushed)
	{
		return false;
	}
	return true;
}

bool IsKilled::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	bool isKilled = pAnimationComponent->GetIsDestroyed();

	return isKilled; 
}
