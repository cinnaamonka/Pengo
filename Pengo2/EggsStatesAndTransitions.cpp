#include "EggsStatesAndTransitions.h"
#include <TimeManager.h>

void BreakingEggState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(3);
	pAnimationComponent->SetFramesPerSec(1);
	pAnimationComponent->SetHorizontalOffset(1);
	pAnimationComponent->SetVerticalOffset(0);
}

void BreakingEggState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	AnimationUpdate(pAnimationComponent);

	int currentAnimationFrame = pAnimationComponent->GetAnimationFrame();

	int numberOfFrames = pAnimationComponent->GetNumberOfFrames();

	if (currentAnimationFrame == numberOfFrames - 1)
	{
		pAnimationComponent->Destroy();
	}
}

void WaitingState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(1);
	pAnimationComponent->SetFramesPerSec(1);
	pAnimationComponent->SetHorizontalOffset(0);
	pAnimationComponent->SetVerticalOffset(0);
}

void WaitingState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	float timeOffset = pAnimationComponent->GetTimeOffset();

	timeOffset += GameEngine::TimeManager::GetElapsed();

	pAnimationComponent->SetTimeOffset(timeOffset);
}

bool IsEggBroken::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	bool isDestroyed = pAnimationComponent->GetIsDestroyed();

	return isDestroyed;
}

void BrokenEggState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	bool isDestroyed = pAnimationComponent->GetIsDestroyed();

	if (isDestroyed)
	{
		pAnimationComponent->Destroy();
	}
}

bool IsWaiting::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	float timeOffset = pAnimationComponent->GetTimeOffset(); 

	return (timeOffset >= 1.0f);
}
