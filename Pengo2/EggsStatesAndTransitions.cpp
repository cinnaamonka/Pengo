#include "EggsStatesAndTransitions.h"
#include <TimeManager.h>

void BreakingEggState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
{

	pBlackboard->ChangeData("NumberOfFrames", 2);
	pBlackboard->ChangeData("FramesPerSec", 1);
	pBlackboard->ChangeData("HorizontalOffset", 1);
	pBlackboard->ChangeData("VerticalOffset", 0);
}

void BreakingEggState::OnExit(GameEngine::BlackboardComponent*)
{

}

void BreakingEggState::Update(GameEngine::BlackboardComponent* pBlackboard)
{
	AnimationUpdate(pBlackboard);

	int currentAnimationFrame;
	pBlackboard->GetData("AnimationFrame", currentAnimationFrame);

	int numberOfFrames;
	pBlackboard->GetData("NumberOfFrames", numberOfFrames);

	if (currentAnimationFrame == numberOfFrames - 1)
	{
		pBlackboard->ChangeData("Destroyed", true);
	}
}

void WaitingState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
{
	pBlackboard->ChangeData("NumberOfFrames", 1);
	pBlackboard->ChangeData("FramesPerSec", 1);
	pBlackboard->ChangeData("HorizontalOffset", 0);
	pBlackboard->ChangeData("VerticalOffset", 0);
}

void WaitingState::Update(GameEngine::BlackboardComponent* pBlackboard)
{
	float timeOffset;
	pBlackboard->GetData("TimeOffset", timeOffset);

	timeOffset += GameEngine::TimeManager::GetElapsed();

	pBlackboard->ChangeData("TimeOffset", timeOffset);
}

bool IsEggBroken::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
{
	bool isDestroyed;
	pBlackboard->GetData("Destroyed", isDestroyed);

	return isDestroyed;
}

void BrokenEggState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
{
	bool isDestroyed;
	pBlackboard->GetData("Destroyed", isDestroyed);

	if (isDestroyed)
	{
		pBlackboard->Destroy();
	}
}

bool IsWaiting::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
{
	float timeOffset;
	pBlackboard->GetData("TimeOffset", timeOffset);

	return (timeOffset >= 1.0f);
}
