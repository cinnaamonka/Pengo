#pragma once
#include "BaseComponent.h"
#include <map>
#include "AnimationComponent.h"

namespace GameEngine
{
	class Gameobject;

	class FSMState
	{
	public:
		FSMState() = default;
		virtual ~FSMState() = default;
		

		virtual void OnEnter(AnimationComponent* pBlackboard) = 0;
		virtual void OnExit(AnimationComponent* pBlackboard) = 0;
		virtual void Update(AnimationComponent* pBlackboard) = 0;
	};

	class FSMCondition
	{
	public:
		FSMCondition()
		{

		}
		virtual ~FSMCondition() = default;
		virtual bool Evaluate(AnimationComponent* pBlackboard) const = 0;
	};

	class FSM : public BaseComponent
	{
	public:
		FSM(GameObject* pGameObject, FSMState* startState, AnimationComponent* pBlackboard);
		virtual ~FSM() = default;

		void AddTransition(FSMState* startState, FSMState* toState, FSMCondition* transition); 
		virtual void Update() override;

		FSM(const FSM& other) = delete;
		FSM& operator=(const FSM& other) = delete;
		FSM(FSM&& other) noexcept = delete;
		FSM& operator=(FSM&& other) noexcept = delete;

	protected:
		void ChangeState(FSMState* newState);
	protected:
		typedef std::pair<FSMCondition*, FSMState*> TransitionStatePair;
		typedef std::vector<TransitionStatePair> Transitions;

		using TransitionsMap = std::map<FSMState*, Transitions>;

		TransitionsMap m_Transitions;
		FSMState* m_pCurrentState = nullptr;
		AnimationComponent* m_pAnimationComponent = nullptr;
	};

}

