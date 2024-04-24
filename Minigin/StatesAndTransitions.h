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
	class PushingState : public GameEngine::FSMState
	{
	public:
		PushingState() = default;
		~PushingState() = default;

		virtual void OnEnter(GameEngine::Blackboard* pBlackboard) override;
		virtual void OnExit(GameEngine::Blackboard* pBlackboard) override;
		virtual void Update(GameEngine::Blackboard* pBlackboard) override;

	};
	class StaticBlockState : public GameEngine::FSMState
	{
	public:
		StaticBlockState() = default;
		~StaticBlockState() = default;

		virtual void OnEnter(GameEngine::Blackboard* pBlackboard) override;
		virtual void OnExit(GameEngine::Blackboard* pBlackboard) override;
		virtual void Update(GameEngine::Blackboard* pBlackboard) override;

	};
	class BreakingBlockState : public GameEngine::FSMState
	{
	public:
		BreakingBlockState() = default;
		~BreakingBlockState() = default;

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
	class IsBlockPushed : public GameEngine::FSMCondition
	{
	public:
		IsBlockPushed() = default;
		~IsBlockPushed() = default;

		virtual bool Evaluate(GameEngine::Blackboard* pBlackboard) const override;
	};
	class IsBlockNotPushed : public GameEngine::FSMCondition
	{
	public:
		IsBlockNotPushed() = default;
		~IsBlockNotPushed() = default;

		virtual bool Evaluate(GameEngine::Blackboard* pBlackboard) const override;
	};
	class IsBlockBreaking : public GameEngine::FSMCondition
	{
	public:
		IsBlockBreaking() = default;
		~IsBlockBreaking() = default;

		virtual bool Evaluate(GameEngine::Blackboard* pBlackboard) const override;
	};

	void AnimationUpdate(GameEngine::Blackboard* pBlackboard);
}

