#pragma once
#include <Helpers.h>
#include <BlackboardComponent.h>

//ENEMY STATES
class MovingState : public GameEngine::FSMState
{
public:
	MovingState() = default;
	~MovingState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;

};

class AttackState : public GameEngine::FSMState
{
public:
	AttackState() = default;
	~AttackState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;

};
class DyingState : public GameEngine::FSMState
{
public:
	DyingState() = default;
	~DyingState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;

};

//ENEMY CONDITIONS
class HasAttacked : public GameEngine::FSMCondition
{
public:
	HasAttacked() = default;
	~HasAttacked() = default;

	virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
};
class HasNotAttacked : public GameEngine::FSMCondition
{
public:
	HasNotAttacked() = default;
	~HasNotAttacked() = default;

	virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
};


