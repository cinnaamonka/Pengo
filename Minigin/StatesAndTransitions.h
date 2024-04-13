#pragma once
#include "Helpers.h"

namespace GameEngine
{
	class IdleState : public GameEngine::FSMState
	{
	public:
		IdleState() = default;
		~IdleState() = default;

		virtual void OnEnter(GameEngine::Blackboard* pBlackboard) override;
		virtual void OnExit(GameEngine::Blackboard* pBlackboard) override;
		virtual void Update(GameEngine::Blackboard* pBlackboard) override;
	};
	class RunningState : public GameEngine::FSMState
	{
	public:
		RunningState() = default;
		~RunningState() = default;

		virtual void OnEnter(GameEngine::Blackboard* pBlackboard) override;
		virtual void OnExit(GameEngine::Blackboard* pBlackboard) override;
		virtual void Update(GameEngine::Blackboard* pBlackboard) override;

	};

	class IsInputGiven : public GameEngine::FSMCondition
	{
	public:
		IsInputGiven() = default;
		~IsInputGiven() = default;

		virtual bool Evaluate(GameEngine::Blackboard* pBlackboard) const override;
	};
	class IsInputNotGiven : public GameEngine::FSMCondition
	{
	public:
		IsInputNotGiven() = default;
		~IsInputNotGiven() = default;

		virtual bool Evaluate(GameEngine::Blackboard* pBlackboard) const override;
	};

}

