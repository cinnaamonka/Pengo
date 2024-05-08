#pragma once
#include <Helpers.h>
#include <BlackboardComponent.h>

class IdleState : public GameEngine::FSMState
{
public:
	IdleState() = default;
	~IdleState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;
};
class RunningState : public GameEngine::FSMState
{
public:
	RunningState() = default;
	~RunningState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;

};
class PushingState : public GameEngine::FSMState
{
public:
	PushingState() = default;
	~PushingState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;

};

class PlayerDyingState : public GameEngine::FSMState
{
public:
	PlayerDyingState() = default;
	~PlayerDyingState() = default;

	virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void OnExit(GameEngine::BlackboardComponent* pBlackboard) override;
	virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;

};

class IsInputGiven : public GameEngine::FSMCondition
{
public:
	IsInputGiven() = default;
	~IsInputGiven() = default;

	virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
};
class IsInputNotGiven : public GameEngine::FSMCondition
{
public:
	IsInputNotGiven() = default;
	~IsInputNotGiven() = default;

	virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
};

class IsBlockPushed : public GameEngine::FSMCondition
{
public:
	IsBlockPushed() = default;
	~IsBlockPushed() = default;

	virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
};
class IsBlockNotPushed : public GameEngine::FSMCondition
{
public:
	IsBlockNotPushed() = default;
	~IsBlockNotPushed() = default;

	virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
};
class IsKilled : public GameEngine::FSMCondition
{
public:
	IsKilled() = default;
	~IsKilled() = default;

	virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
};