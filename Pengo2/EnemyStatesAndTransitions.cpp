#include "EnemyStatesAndTransitions.h"

void AttackState::OnEnter(GameEngine::BlackboardComponent*)
{
}

void AttackState::OnExit(GameEngine::BlackboardComponent*)
{
}

void AttackState::Update(GameEngine::BlackboardComponent*)
{
}

void MovingState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
{
	glm::vec3 movementDirection;
	pBlackboard->GetData("MovementDirection", movementDirection);

	if (movementDirection.x > 0 || movementDirection.x < 0)
	{
		pBlackboard->ChangeData("HorizontalOffset", 2); 
	}
	else if (movementDirection.y < 0)
	{
		pBlackboard->ChangeData("HorizontalOffset", 0);
	}
	else if (movementDirection.y > 0)
	{
		pBlackboard->ChangeData("HorizontalOffset", 4);
	}
	pBlackboard->ChangeData("NumberOfFrames", 2);
	pBlackboard->ChangeData("VerticalOffset", 1);
}

void MovingState::OnExit(GameEngine::BlackboardComponent*)
{

}

void MovingState::Update(GameEngine::BlackboardComponent* pBlackboard)
{
	AnimationUpdate(pBlackboard);
}


bool HasAttacked::Evaluate(GameEngine::BlackboardComponent*) const
{
	return false;
}

bool HasNotAttacked::Evaluate(GameEngine::BlackboardComponent*) const
{
	return false;
}

void DyingState::OnEnter(GameEngine::BlackboardComponent* )
{

}

void DyingState::OnExit(GameEngine::BlackboardComponent* )
{
}

void DyingState::Update(GameEngine::BlackboardComponent* )
{
}
