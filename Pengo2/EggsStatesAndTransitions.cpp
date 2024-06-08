#include "EggsStatesAndTransitions.h"
#include <TimeManager.h>

void BreakingEggState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(m_NumberOfEnterStateFrames);
	pAnimationComponent->SetFramesPerSec(m_FramesPerSec);
	pAnimationComponent->SetHorizontalOffset(m_HorizontalOffset);
	pAnimationComponent->SetVerticalOffset(m_VerticalOffset);
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
	pAnimationComponent->SetNumberOfFrames(m_NumberOfEnterStateFrames);
	pAnimationComponent->SetFramesPerSec(m_FramesPerSec);
	pAnimationComponent->SetHorizontalOffset(m_HorizontalOffset);
	pAnimationComponent->SetVerticalOffset(m_VerticalOffset);
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
