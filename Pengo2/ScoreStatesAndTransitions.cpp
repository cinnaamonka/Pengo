#include "ScoreStatesAndTransitions.h"
#include <TimeManager.h>

void ScoreAppearingState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(m_NumberOfEnterStateFrames);
	pAnimationComponent->SetFramesPerSec(m_FramesPerSec);
	pAnimationComponent->SetHorizontalOffset(m_HorizontalOffset);
	pAnimationComponent->SetVerticalOffset(m_VerticalOffset);
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
	pAnimationComponent->SetNumberOfFrames(m_NumberOfEnterStateFrames);
	pAnimationComponent->SetFramesPerSec(m_FramesPerSec);
	pAnimationComponent->SetHorizontalOffset(m_HorizontalOffset);
	pAnimationComponent->SetVerticalOffset(m_VerticalOffset);
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

	return (timeOffset >= m_MaxWaitingTime);
}
