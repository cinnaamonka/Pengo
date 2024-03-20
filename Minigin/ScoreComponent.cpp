#include "ScoreComponent.h"


namespace GameEngine
{
	ScoreComponent::ScoreComponent(GameObject* pGameObject) :
		BaseComponent(pGameObject), m_Score(0) 
	{
		
	}

	void ScoreComponent::AddScore(int score)
	{
		m_Score += score;
		
		CreateMessage(m_Score);
	}

	void ScoreComponent::RemoveScore(int score)
	{
		m_Score -= score;

		CreateMessage(m_Score);
	}

}