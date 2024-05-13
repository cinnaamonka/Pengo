#include "AIFSM.h"

namespace GameEngine
{
	AIFSM::AIFSM(GameObject* pGameObject, FSMState* startState, AnimationComponent* pAnimationComponent) :
		FSM(pGameObject, startState, pAnimationComponent)
	{}
}