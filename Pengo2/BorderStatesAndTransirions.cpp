#include "BorderStatesAndTransirions.h"

void VibratingState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(2); 
	pAnimationComponent->SetFramesPerSec(1); 
	pAnimationComponent->SetHorizontalOffset(0); 
	pAnimationComponent->SetVerticalOffset(0); 
}

void VibratingState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	AnimationUpdate(pAnimationComponent);

	int currentAnimationFrame = pAnimationComponent->GetAnimationFrame();

	int numberOfFrames = pAnimationComponent->GetNumberOfFrames();

	if (currentAnimationFrame == numberOfFrames - 1)
	{
		pAnimationComponent->SetIsDestroyed(true);
	}
}

void StopVibrating::OnEnter(GameEngine::AnimationComponent*)
{

}

bool HasFinishedVibrating::Evaluate(GameEngine::AnimationComponent* ) const
{
	return false;
}
