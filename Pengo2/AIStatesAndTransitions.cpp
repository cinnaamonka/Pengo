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

	float speed;
	pBlackboard->GetData("Speed", speed);

	if (direction.x != 0)
	{
		pos.x += speed * direction.x;
	}
	if (direction.y != 0)
	{
		pos.y += speed * direction.y;
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

	float speed;
	pBlackboard->GetData("Speed", speed);

	if (direction.x != 0)
	{
		pos.x += speed * direction.x;
	}
	if (direction.y != 0)
	{
		pos.y += speed * direction.y;
	}

	pBlackboard->ChangeData("Pos", pos);
}

bool HasNoticedActor::Evaluate(GameEngine::BlackboardComponent* pBlackboard) const
{
	bool isChasing;
	pBlackboard->GetData("IsChasing", isChasing);

	return isChasing;
}
