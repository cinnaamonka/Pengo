#include "BorderStatesAndTransirions.h"

void VibratingState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	bool isBorderHorizontal = pAnimationComponent->GetIsHorizontal();

	if (isBorderHorizontal)
	{
		pAnimationComponent->SetHorizontalOffset(0);
		pAnimationComponent->SetVerticalOffset(1);
	}
	else
	{
		pAnimationComponent->SetHorizontalOffset(1);
		pAnimationComponent->SetVerticalOffset(0);
	}
	pAnimationComponent->SetNumberOfFrames(2);
	pAnimationComponent->SetFramesPerSec(10);

}


void VibratingState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	AnimationUpdate(pAnimationComponent);
}

void StopVibrating::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetHorizontalOffset(0);
	pAnimationComponent->SetVerticalOffset(0);
	pAnimationComponent->SetNumberOfFrames(1);
	pAnimationComponent->SetFramesPerSec(10);
}


bool HasFinishedVibrating::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	if (pAnimationComponent->GetWasPushed())
	{
		return true;
	}
	return false;
}

bool IsVibrating::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	if (pAnimationComponent->GetWasPushed())
	{
		return false;
	}
	return true;
}
