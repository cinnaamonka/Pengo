#pragma once
#include "FSM.h"

namespace GameEngine
{
	class AIFSM : public GameEngine::FSM
	{
	public:
		AIFSM(GameObject* pGameObject, FSMState* startState, AnimationComponent* pBlackboard);
	};
}
