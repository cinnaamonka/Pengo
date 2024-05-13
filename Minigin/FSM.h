#pragma once
#include "BaseComponent.h"
#include <map>
#include <string>
#include <unordered_map>
#include "Helpers.h"
#include "AnimationComponent.h"
#include "BlackboardComponent.h"

namespace GameEngine
{
	class Gameobject;

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

		std::map<FSMState*, Transitions> m_Transitions;
		FSMState* m_pCurrentState = nullptr;
		AnimationComponent* m_pAnimationComponent = nullptr;
		//BlackboardComponent* m_pBlackboard = nullptr;
	};

}

