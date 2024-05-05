#include "AIFSM.h"

namespace GameEngine
{
	AIFSM::AIFSM(GameObject* pGameObject, FSMState* startState, BlackboardComponent* pBlackboard) :
		FSM(pGameObject, startState, pBlackboard)
	{}
}