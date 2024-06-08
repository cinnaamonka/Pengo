#pragma once
#include "FSM.h"

namespace GameEngine
{
	class AIFSM final: public GameEngine::FSM
	{
	public:
		AIFSM(GameObject* pGameObject, FSMState* startState, AnimationComponent* pBlackboard);
	
		virtual ~AIFSM() = default;
		AIFSM(const AIFSM& other) = delete;
		AIFSM(AIFSM&& other) = delete;
		AIFSM& operator=(const AIFSM& other) = delete;
		AIFSM& operator=(AIFSM&& other) = delete;

	};
}
