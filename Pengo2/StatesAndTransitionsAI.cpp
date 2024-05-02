#include "StatesAndTransitionsAI.h"

void PatrolState::OnEnter(GameEngine::BlackboardComponent* pBlackboard)
{

}

void PatrolState::OnExit(GameEngine::BlackboardComponent*)
{
}

void PatrolState::Update(GameEngine::BlackboardComponent*)
{
}

void ChaseState::OnEnter(GameEngine::BlackboardComponent*)
{
}

void ChaseState::OnExit(GameEngine::BlackboardComponent*)
{
}

void ChaseState::Update(GameEngine::BlackboardComponent*)
{
}

bool HasNoticedActor::Evaluate(GameEngine::BlackboardComponent*) const
{
	return false;
}
