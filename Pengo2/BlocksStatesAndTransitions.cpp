#include "BlocksStatesAndTransitions.h"
#include <AnimationComponent.h>

void StaticBlockState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(1);
	pAnimationComponent->SetHorizontalOffset(0);
	pAnimationComponent->SetVerticalOffset(0);
}
void StaticBlockState::OnExit(GameEngine::AnimationComponent*)
{}

void StaticBlockState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	AnimationUpdate(pAnimationComponent);
}

void BreakingBlockState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(9);
	pAnimationComponent->SetFramesPerSec(10);
	pAnimationComponent->SetHorizontalOffset(7);
	pAnimationComponent->SetVerticalOffset(0);
}

void BreakingBlockState::OnExit(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(2);
	pAnimationComponent->SetFramesPerSec(1);
	pAnimationComponent->SetHorizontalOffset(1);
	pAnimationComponent->SetVerticalOffset(0);
}

void BreakingBlockState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{

	AnimationUpdate(pAnimationComponent);

	int currentAnimationFrame = pAnimationComponent->GetAnimationFrame();

	int numberOfFrames = pAnimationComponent->GetNumberOfFrames();

	if (currentAnimationFrame == numberOfFrames - 1)
	{
		pAnimationComponent->Destroy();
	}
}

void FlickeringBlockState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(6);
	pAnimationComponent->SetFramesPerSec(2);
	pAnimationComponent->SetHorizontalOffset(0);
	pAnimationComponent->SetVerticalOffset(0);
}

void FlickeringBlockState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	AnimationUpdate(pAnimationComponent);

	int animTimes = pAnimationComponent->GetAnimationTimes();

	animTimes++;
	pAnimationComponent->SetAnimationTimes(animTimes);

}

bool IsBlockBreaking::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	bool wasBlockDestroyed = pAnimationComponent->GetIsDestroyed(); 

	return wasBlockDestroyed;
}

bool IsBlockNotBreaking::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	bool wasBlockDestroyed = pAnimationComponent->GetIsDestroyed();

	return !wasBlockDestroyed;
}

bool IsBlockFinishedFlickering::Evaluate(GameEngine::AnimationComponent* pAnimationComponent) const
{
	int animTimes = pAnimationComponent->GetAnimationTimes(); 

	return animTimes >= 150.f;
}