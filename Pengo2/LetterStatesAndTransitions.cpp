#include "LetterStatesAndTransitions.h"
#include <Helpers.h>
void StaticLetterState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(1);
	pAnimationComponent->SetFramesPerSec(1);
}


bool ShouldStartFlyckering::Evaluate(GameEngine::AnimationComponent* ) const
{
	return false;
}

void FlyckeringLetterState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(2);
	pAnimationComponent->SetFramesPerSec(10);
	pAnimationComponent->SetHorizontalOffset(0);
	pAnimationComponent->SetVerticalOffset(0);
}

void FlyckeringLetterState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	GameEngine::AnimationUpdate(pAnimationComponent);
}
