#pragma once
#include "FSM.h"
#include "Helpers.h"
#include "TransformComponent.h"


namespace GameEngine
{
	GameEngine::FSM::FSM(GameObject* pGameObject, FSMState* startState, AnimationComponent* pAnimationComponent) :
		BaseComponent(pGameObject),
		m_pCurrentState(nullptr),
		m_pAnimationComponent(pAnimationComponent)
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
		TransitionsMap::const_iterator it = m_Transitions.find(m_pCurrentState);

		if (it != m_Transitions.cend())
		{
			const Transitions& transitions = it->second;

			for (const TransitionStatePair& transitionState : transitions)
			{
				FSMCondition* pCondition = transitionState.first;
				FSMState *pState = transitionState.second;

				if (pCondition->Evaluate(m_pAnimationComponent))
				{
					ChangeState(pState);
				}
			}
		}

		m_pCurrentState->Update(m_pAnimationComponent);
		
	}

	void GameEngine::FSM::ChangeState(FSMState* newState)
	{

		if (m_pCurrentState != nullptr)
		{
			m_pCurrentState->OnExit(m_pAnimationComponent);
		}

		m_pCurrentState = newState;

		if (m_pCurrentState != nullptr)
		{
			m_pCurrentState->OnEnter(m_pAnimationComponent);
		}
	}
}

