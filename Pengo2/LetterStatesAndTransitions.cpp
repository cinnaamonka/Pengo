#include "LetterStatesAndTransitions.h"
#include <Helpers.h>
void StaticLetterState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(m_NumberOfEnterStateFrames);
	pAnimationComponent->SetFramesPerSec(m_FramesPerSec);
}

void StaticLetterState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	GameEngine::AnimationUpdate(pAnimationComponent);

	if (pAnimationComponent->GetAnimationTimes() >= m_MaxAnimationTimesAmount)
	{
		pAnimationComponent->SetShouldFlyckering(true);
		pAnimationComponent->SetAnimationTimes(0);
	}
	int currentAnimationIteration = pAnimationComponent->GetAnimationTimes();
	currentAnimationIteration++;
	pAnimationComponent->SetAnimationTimes(currentAnimationIteration);
}

bool ShouldStartFlyckering::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	return pAnimationComponent->GetShouldFlyckering();
}

void FlyckeringLetterState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(m_NumberOfEnterStateFrames);
	pAnimationComponent->SetFramesPerSec(m_FramesPerSec);

	int verticalOffset = pAnimationComponent->GetVerticalOffset(); 

	pAnimationComponent->SetVerticalOffset(verticalOffset + 2);
}

void FlyckeringLetterState::OnExit(GameEngine::AnimationComponent* pAnimationComponent)
{
	int verticalOffset = pAnimationComponent->GetVerticalOffset();

	pAnimationComponent->SetVerticalOffset(verticalOffset - 2);
	
}

void FlyckeringLetterState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	GameEngine::AnimationUpdate(pAnimationComponent);
	
	if (pAnimationComponent->GetAnimationTimes() >= m_MaxAnimationTimesAmount)
	{
		pAnimationComponent->SetShouldFlyckering(false);
		pAnimationComponent->SetAnimationTimes(0);
	}
	int currentAnimationIteration = pAnimationComponent->GetAnimationTimes();
	currentAnimationIteration++;
	pAnimationComponent->SetAnimationTimes(currentAnimationIteration);
}

bool ShouldStopFlyckering::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	return !pAnimationComponent->GetShouldFlyckering();
}
