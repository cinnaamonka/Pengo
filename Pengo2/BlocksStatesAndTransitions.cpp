#include "BlocksStatesAndTransitions.h"
#include <AnimationComponent.h>

void StaticBlockState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(m_NumberOfEnterStateFrames);
	pAnimationComponent->SetHorizontalOffset(m_HorizontalOffset);
	pAnimationComponent->SetVerticalOffset(m_VerticalOffset);
}
void StaticBlockState::OnExit(GameEngine::AnimationComponent*)
{}

void StaticBlockState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	AnimationUpdate(pAnimationComponent);
}

void BreakingBlockState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetNumberOfFrames(m_NumberOfEnterStateFrames);
	pAnimationComponent->SetFramesPerSec(m_FramesPerSec);
	pAnimationComponent->SetHorizontalOffset(m_HorizontalOffset);
	pAnimationComponent->SetVerticalOffset(m_VerticalOffset);
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
	pAnimationComponent->SetNumberOfFrames(m_NumberOfEnterStateFrames);
	pAnimationComponent->SetFramesPerSec(m_FramesPerSec);
	pAnimationComponent->SetHorizontalOffset(m_HorizontalOffset);
	pAnimationComponent->SetVerticalOffset(m_VerticalOffset);
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

	return animTimes >= m_MaxAnimationTimes;
}