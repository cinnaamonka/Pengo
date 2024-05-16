#include "ScoreStatesAndTransitions.h"
#include <TimeManager.h>

void ScoreAppearingState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(3);
	pAnimationComponent->SetFramesPerSec(1);
	pAnimationComponent->SetHorizontalOffset(1);
	pAnimationComponent->SetVerticalOffset(0);
}

void ScoreAppearingState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	AnimationUpdate(pAnimationComponent); 

	int currentAnimationFrame = pAnimationComponent->GetAnimationFrame(); 

	int numberOfFrames = pAnimationComponent->GetNumberOfFrames();

	if (currentAnimationFrame == numberOfFrames - 1)
	{
		pAnimationComponent->Destroy();
	}
}

void ScoreWaitingState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(1);
	pAnimationComponent->SetFramesPerSec(1);
	pAnimationComponent->SetHorizontalOffset(0);
	pAnimationComponent->SetVerticalOffset(0);
}

void ScoreWaitingState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	float timeOffset = pAnimationComponent->GetTimeOffset();

	timeOffset += GameEngine::TimeManager::GetElapsed();

	pAnimationComponent->SetTimeOffset(timeOffset);
}

bool IsScoreWaiting::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	float timeOffset = pAnimationComponent->GetTimeOffset();

	return (timeOffset >= 3.0f);
}
