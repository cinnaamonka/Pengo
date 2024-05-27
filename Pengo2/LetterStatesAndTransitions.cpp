#include "LetterStatesAndTransitions.h"
#include <Helpers.h>
void StaticLetterState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(1);
	pAnimationComponent->SetFramesPerSec(1);
}

void StaticLetterState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	GameEngine::AnimationUpdate(pAnimationComponent);

	if (pAnimationComponent->GetAnimationTimes() >= 50)
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
	pAnimationComponent->SetNumberOfFrames(1);
	pAnimationComponent->SetFramesPerSec(1);

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
	
	if (pAnimationComponent->GetAnimationTimes() >= 50)
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
