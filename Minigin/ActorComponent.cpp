#pragma once
#include "ActorComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include "FSM.h"

namespace GameEngine
{
	GameEngine::ActorComponent::ActorComponent(GameObject* pGameObject)
		:BaseComponent(pGameObject),
		m_Score(0),
		m_LifesAmount(3),
		m_Speed(30.0f),
		m_DestTextureRect{}
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
	void ActorComponent::ChangeTexture(int currentAnimationFrame, int currentHorizontalOffset, int currentVerticalOffset )
	{
		Rect previousDimensions = GetGameObject()->GetComponent<GameEngine::TransformComponent>()->GetDimensions();

		Rect currentDimensions
		{
			currentHorizontalOffset * previousDimensions.width + currentAnimationFrame * previousDimensions.width,
			currentVerticalOffset * previousDimensions.height + previousDimensions.bottom,
			previousDimensions.width,
			previousDimensions.height
		};
	    
		GetGameObject()->GetComponent<GameEngine::TransformComponent>()->SetDimensions(currentDimensions);
	}
	void ActorComponent::Update()
	{
		int currentAnimationFrame;
		GetGameObject()->GetComponent<GameEngine::FSM>()->GetBlackboard()->GetData("AnimationFrame", currentAnimationFrame);

		int currentOffset;
		GetGameObject()->GetComponent<GameEngine::FSM>()->GetBlackboard()->GetData("HorizontalOffset", currentOffset);


		ChangeTexture(currentAnimationFrame,currentOffset);
	}
}
