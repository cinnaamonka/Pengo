#pragma once
#include "ActorComponent.h"

namespace GameEngine
{
	GameEngine::ActorComponent::ActorComponent(GameObject* pGameObject)
		:BaseComponent(pGameObject),
		m_LifesAmount(3),
		m_Speed(30.0f),
		m_DestTextureRect{},
		m_CanCollisionBeChecked(false),
		m_Score(0)
	{}

	void ActorComponent::Damage(int damage)
	{
		m_LifesAmount -= damage;

		m_LifesAmountChanged.CreateMessage(m_LifesAmount);

		m_StateChanged.CreateMessage(GameEngine::State::PlayerDied);
	}
	void ActorComponent::Win()
	{
		m_StateChanged.CreateMessage(GameEngine::State::Victory);  
	}
}
