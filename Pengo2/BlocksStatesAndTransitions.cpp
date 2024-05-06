#include "BlocksStatesAndTransitions.h"

void StaticBlockState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
{
	pBlackboard->ChangeData("NumberOfFrames", 1);
	pBlackboard->ChangeData("HorizontalOffset", 0);
	pBlackboard->ChangeData("VerticalOffset", 0);
}
void StaticBlockState::OnExit(GameEngine::BlackboardComponent* pBlackboard)
{
	pBlackboard->ChangeData("WasBlockDestroyed", false);
}
void StaticBlockState::Update(GameEngine::BlackboardComponent* pBlackboard)
{
	pBlackboard = pBlackboard;

	AnimationUpdate(pBlackboard);
}

void BreakingBlockState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
{
	pBlackboard->ChangeData("NumberOfFrames", 9);
	pBlackboard->ChangeData("FramesPerSec", 10);
	pBlackboard->ChangeData("HorizontalOffset", 7);
	pBlackboard->ChangeData("VerticalOffset", 0);
}

void BreakingBlockState::OnExit(GameEngine::BlackboardComponent* pBlackboard)
{
	bool isDestroyed;
	pBlackboard->GetData("Destroyed", isDestroyed);

	if (isDestroyed)
	{
		pBlackboard->Destroy();
	}

}

void BreakingBlockState::Update(GameEngine::BlackboardComponent* pBlackboard)
{
	AnimationUpdate(pBlackboard);

	int currentAnimationFrame;
	pBlackboard->GetData("AnimationFrame", currentAnimationFrame);

	int numberOfFrames;
	pBlackboard->GetData("NumberOfFrames", numberOfFrames);

	if (currentAnimationFrame == numberOfFrames - 1)
	{
		pBlackboard->ChangeData("WasBlockDestroyed", false);
		pBlackboard->ChangeData("Destroyed", true);
	}
}

void FlickeringBlockState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
{
	pBlackboard->ChangeData("NumberOfFrames", 6);
	pBlackboard->ChangeData("FramesPerSec", 2);
	pBlackboard->ChangeData("HorizontalOffset", 0);
	pBlackboard->ChangeData("VerticalOffset", 0);
}

void FlickeringBlockState::Update(GameEngine::BlackboardComponent* pBlackboard)
{
	AnimationUpdate(pBlackboard);

	int animTimes;
	pBlackboard->GetData("AnimationTimes", animTimes);

	animTimes++;
	pBlackboard->ChangeData("AnimationTimes", animTimes);

}

bool IsBlockBreaking::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
{
	bool wasBlockDedtroyed;
	pBlackboard->GetData("WasBlockDestroyed", wasBlockDedtroyed);

	return wasBlockDedtroyed;
}

bool IsBlockNotBreaking::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
{
	bool wasBlockDedtroyed;
	pBlackboard->GetData("WasBlockDestroyed", wasBlockDedtroyed);

	return !wasBlockDedtroyed;
}

bool IsBlockFinishedFlickering::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
{
	int animTimes;
	pBlackboard->GetData("AnimationTimes", animTimes);

	return animTimes >= 150.f;
}