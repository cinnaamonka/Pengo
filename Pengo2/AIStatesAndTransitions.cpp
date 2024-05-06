#include "AIStatesAndTransitions.h"

void PatrolState::OnEnter(GameEngine::BlackboardComponent*)
{

}

void PatrolState::OnExit(GameEngine::BlackboardComponent*)
{
}

void PatrolState::Update(GameEngine::BlackboardComponent* pBlackboard)
{
	glm::vec3 pos;
	pBlackboard->GetData("Pos", pos);

	glm::vec3 direction;
	pBlackboard->GetData("MovementDirection", direction);

	if (direction.x != 0)
	{
		pos.x += 0.5f * direction.x;
	}
	if (direction.y != 0)
	{
		pos.y += 0.5f * direction.y;
	}

	pBlackboard->ChangeData("Pos", pos);
}

void ChaseState::OnEnter(GameEngine::BlackboardComponent*)
{
}

void ChaseState::OnExit(GameEngine::BlackboardComponent*)
{
}

void ChaseState::Update(GameEngine::BlackboardComponent* pBlackboard)
{
	glm::vec3 pos;
	pBlackboard->GetData("Pos", pos);

	glm::vec3 direction;
	pBlackboard->GetData("MovementDirection", direction);

	if (direction.x != 0)
	{
		pos.x += 0.1f * direction.x;
	}
	if (direction.y != 0)
	{
		pos.y += 0.1f * direction.y;
	}

	pBlackboard->ChangeData("Pos", pos);
}

bool HasNoticedActor::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
{
	bool isChasing;
	pBlackboard->GetData("IsChasing", isChasing);

	return isChasing;
}
