#pragma once
#include "FSM.h"
#include "Helpers.h"
#include "TransformComponent.h"

namespace GameEngine
{
	GameEngine::FSM::FSM(GameObject* pGameObject, FSMState* startState, Blackboard* pBlackboard) :
		BaseComponent(pGameObject),
		m_pCurrentState(nullptr),
		m_pBlackboard(pBlackboard)
	{
		ChangeState(startState);
	}

	void GameEngine::FSM::AddTransition(FSMState* startState, FSMState* toState, FSMCondition* condition)
	{
		auto it = m_Transitions.find(startState);
		if (it == m_Transitions.end())
		{
			m_Transitions[startState] = Transitions();
		}

		m_Transitions[startState].push_back(std::make_pair(condition, toState));
	}

	void GameEngine::FSM::Update()
	{
		const auto& transitionItr = m_Transitions.find(m_pCurrentState);

		if (transitionItr != m_Transitions.end())
		{
			for (const auto& transitionState : transitionItr->second)
			{
				if (transitionState.first->Evaluate(m_pBlackboard))
				{
					ChangeState(transitionState.second);
				}
			}
		}
	}

	Blackboard* GameEngine::FSM::GetBlackboard() const
	{
		return m_pBlackboard;
	}

	void GameEngine::FSM::ChangeState(FSMState* newState)
	{
		if (m_pCurrentState != nullptr)
		{
			m_pCurrentState->OnExit(m_pBlackboard);
		}

		m_pCurrentState = newState;

		if (m_pCurrentState != nullptr)
		{
			m_pCurrentState->OnEnter(m_pBlackboard);
		}
	}
}

