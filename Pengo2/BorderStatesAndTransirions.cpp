#include "BorderStatesAndTransirions.h"

void VibratingState::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	bool isBorderHorizontal = pAnimationComponent->GetIsHorizontal();

	if (isBorderHorizontal)
	{
		pAnimationComponent->SetHorizontalOffset(m_HorizontalOffset);
		pAnimationComponent->SetVerticalOffset(m_VerticalOffset);
	}
	else
	{
		pAnimationComponent->SetHorizontalOffset(m_VerticalOffset);
		pAnimationComponent->SetVerticalOffset(m_HorizontalOffset);
	}
	pAnimationComponent->SetNumberOfFrames(m_NumberOfEnterStateFrames);
	pAnimationComponent->SetFramesPerSec(m_FramesPerSec);

}


void VibratingState::Update(GameEngine::AnimationComponent* pAnimationComponent)
{
	AnimationUpdate(pAnimationComponent);
}

void StopVibrating::OnEnter(GameEngine::AnimationComponent* pAnimationComponent)
{
	pAnimationComponent->SetHorizontalOffset(m_HorizontalOffset);
	pAnimationComponent->SetVerticalOffset(m_VerticalOffset);
	pAnimationComponent->SetNumberOfFrames(m_NumberOfEnterStateFrames);
	pAnimationComponent->SetFramesPerSec(m_FramesPerSec);
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
