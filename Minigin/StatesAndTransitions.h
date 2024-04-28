#pragma once
#include "Helpers.h"
#include "BlackboardComponent.h"

namespace GameEngine
{
	//should be added as a component
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
	class StaticBlockState : public GameEngine::FSMState
	{
	public:
		StaticBlockState() = default;
		~StaticBlockState() = default;

		virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
		virtual void OnExit(GameEngine::BlackboardComponent*) override;
		virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;

	};
	class FlickeringBlockState : public GameEngine::FSMState
	{
	public:
		FlickeringBlockState() = default;
		~FlickeringBlockState() = default;

		virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
		virtual void OnExit(GameEngine::BlackboardComponent*) override;
		virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;

	};

	class BreakingBlockState : public GameEngine::FSMState
	{
	public:
		BreakingBlockState() = default;
		~BreakingBlockState() = default;

		virtual void OnEnter(GameEngine::BlackboardComponent* pBlackboard) override;
		virtual void OnExit(GameEngine::BlackboardComponent* pBlackboard) override;
		virtual void Update(GameEngine::BlackboardComponent* pBlackboard) override;

	};

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
	class IsBlockBreaking : public GameEngine::FSMCondition
	{
	public:
		IsBlockBreaking() = default;
		~IsBlockBreaking() = default;

		virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
	};
	class IsBlockNotBreaking : public GameEngine::FSMCondition
	{
	public:
		IsBlockNotBreaking() = default;
		~IsBlockNotBreaking() = default;

		virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
	};

	class IsBlockFinishedFlickering : public GameEngine::FSMCondition
	{
	public:
		IsBlockFinishedFlickering() = default;
		~IsBlockFinishedFlickering() = default;

		virtual bool Evaluate(GameEngine::BlackboardComponent* pBlackboard) const override;
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

	void AnimationUpdate(GameEngine::BlackboardComponent* pBlackboard);
}

