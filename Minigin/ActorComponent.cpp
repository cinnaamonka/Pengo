#include "ActorComponent.h"

namespace GameEngine
{
	GameEngine::ActorComponent::ActorComponent(GameObject* pGameObject)
		:BaseComponent(pGameObject),
		m_Score(0),
		m_LifesAmount(3),
		m_Speed(30.0f)
	{

	}

	void ActorComponent::AddScore(int score)
	{
		m_Score += score;

		m_ScoreChanged.CreateMessage(m_Score);
	}

	void ActorComponent::RemoveScore(int score)
	{
		m_Score -= score;

		m_ScoreChanged.CreateMessage(m_Score);
	}

	void ActorComponent::Damage(int damage)
	{
		m_LifesAmount -= damage;

		m_LifesAmountChanged.CreateMessage(m_LifesAmount);

		if (m_LifesAmount <= 0)
		{
			m_StateChanged.CreateMessage(GameEngine::State::PlayerDied);
		}
	}
}
