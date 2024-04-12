#pragma once
#include "StatesAndTransitions.h"

namespace GameEngine
{
	void IdleState::OnEnter(Blackboard* pBlackboard)
	{
		pBlackboard = nullptr;
		std::cout << " dd" << std::endl;
	}

	void IdleState::OnExit(Blackboard* pBlackboard)
	{
		pBlackboard = nullptr;
	}

	void IdleState::Update(Blackboard* pBlackboard)
	{
		pBlackboard = nullptr;
	}

	void RunningState::OnEnter(Blackboard* pBlackboard)
	{
		pBlackboard = nullptr;
	}

	void RunningState::OnExit(Blackboard* pBlackboard)
	{
		pBlackboard = nullptr;
	}

	void RunningState::Update(Blackboard* pBlackboard)
	{
		pBlackboard = nullptr;
	}

	bool IsInputGiven::Evaluate(Blackboard* pBlackboard) const
	{
		pBlackboard = nullptr;
		return false;
	}

	bool IsInputNotGiven::Evaluate(Blackboard* pBlackboard) const
	{

		pBlackboard = nullptr;
		return false;
	}
}
