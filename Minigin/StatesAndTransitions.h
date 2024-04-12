#pragma once
#include "Helpers.h"

using namespace GameEngine;

class IdleState : public FSMState
{
public:
	IdleState() = default;
	~IdleState() = default;

	virtual void OnEnter(Blackboard* pBlackboard) override;
	virtual void OnExit(Blackboard* pBlackboard) override;
	virtual void Update(Blackboard* pBlackboard) override;
};
class RunningState : public FSMState
{
public:
	RunningState()= default;
	~RunningState() = default;

	virtual void OnEnter(Blackboard* pBlackboard) override;
	virtual void OnExit(Blackboard* pBlackboard) override;
	virtual void Update(Blackboard* pBlackboard) override;

};

class IsInputGiven : public FSMCondition
{
public:
	IsInputGiven() = default;
	~IsInputGiven() = default;

	virtual bool Evaluate(Blackboard* pBlackboard) const override;
};
class IsInputNotGiven : public FSMCondition
{
public:
	IsInputNotGiven() = default;
	~IsInputNotGiven() = default;

	virtual bool Evaluate(Blackboard* pBlackboard) const override;
};
