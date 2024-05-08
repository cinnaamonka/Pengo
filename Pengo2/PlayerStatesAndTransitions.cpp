#include "PlayerStatesAndTransitions.h"

void IdleState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
{
	pBlackboard->ChangeData("NumberOfFrames", 1);
	pBlackboard->ChangeData("HorizontalOffset", 0);
	pBlackboard->ChangeData("VerticalOffset", 0);
}

void IdleState::OnExit(GameEngine::BlackboardComponent* pBlackboard)
{
	pBlackboard->ChangeData("WasInputGiven", false);
}

void IdleState::Update(GameEngine::BlackboardComponent* pBlackboard)
{
	AnimationUpdate(pBlackboard);
}

void RunningState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
{
	glm::vec3 movementDirection;
	pBlackboard->GetData("MovementDirection", movementDirection);

	if (movementDirection.x > 0 || movementDirection.x < 0)
	{
		pBlackboard->ChangeData("HorizontalOffset", 2);
	}
	else if (movementDirection.y < 0)
	{
		pBlackboard->ChangeData("HorizontalOffset", 4);
	}
	else if (movementDirection.y > 0)
	{
		pBlackboard->ChangeData("HorizontalOffset", 0);
	}
	pBlackboard->ChangeData("NumberOfFrames", 2);
	pBlackboard->ChangeData("VerticalOffset", 0);
}

void RunningState::OnExit(GameEngine::BlackboardComponent* pBlackboard)
{
	pBlackboard->ChangeData("WasInputGiven", false);
}

void RunningState::Update(GameEngine::BlackboardComponent* pBlackboard)
{
	AnimationUpdate(pBlackboard);

	pBlackboard->ChangeData("WasInputGiven", false);
}

void PushingState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
{
	glm::vec3 movementDirection;
	pBlackboard->GetData("MovementDirection", movementDirection);

	if (movementDirection.x > 0 || movementDirection.x < 0)
	{
		pBlackboard->ChangeData("HorizontalOffset", 2);
	}
	else if (movementDirection.y < 0)
	{
		pBlackboard->ChangeData("HorizontalOffset", 4);
	}
	else if (movementDirection.y > 0)
	{
		pBlackboard->ChangeData("HorizontalOffset", 0);
	}
	pBlackboard->ChangeData("NumberOfFrames", 2);
	pBlackboard->ChangeData("VerticalOffset", 1);
}
void PushingState::OnExit(GameEngine::BlackboardComponent* pBlackboard)
{
	pBlackboard->ChangeData("WasBlockPushed", false);
	pBlackboard->ChangeData("WasInputGiven", false);
}
void PushingState::Update(GameEngine::BlackboardComponent* pBlackboard)
{
	AnimationUpdate(pBlackboard);
	pBlackboard->ChangeData("WasBlockPushed", false);
}

void PlayerDyingState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
{
	glm::vec3 movementDirection;
	pBlackboard->GetData("MovementDirection", movementDirection);


	pBlackboard->ChangeData("HorizontalOffset", 0);
	pBlackboard->ChangeData("VerticalOffset", 2);

	pBlackboard->ChangeData("NumberOfFrames", 2);
}

void PlayerDyingState::OnExit(GameEngine::BlackboardComponent*)
{
}

void PlayerDyingState::Update(GameEngine::BlackboardComponent* pBlackboard)
{
	AnimationUpdate(pBlackboard);
}

bool IsInputGiven::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
{
	bool inputWasGiven;
	pBlackboard->GetData("WasInputGiven", inputWasGiven);

	return inputWasGiven;
}

bool IsInputNotGiven::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
{
	bool inputWasGiven;
	pBlackboard->GetData("WasInputGiven", inputWasGiven);

	return !inputWasGiven;
}
bool IsBlockPushed::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
{
	bool wasBlockPushed;
	pBlackboard->GetData("WasBlockPushed", wasBlockPushed);

	return wasBlockPushed;
}
bool IsBlockNotPushed::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
{
	bool wasBlockPushed;
	pBlackboard->GetData("WasBlockPushed", wasBlockPushed);

	float animTime = 0.0f;
	pBlackboard->GetData("AnimationTime", animTime);

	if (animTime <= 1.f && wasBlockPushed)
	{
		return false;
	}
	return true;
}

bool IsKilled::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
{
	bool isKilled; 
	pBlackboard->GetData("IsKilled", isKilled); 

	return isKilled; 
}
