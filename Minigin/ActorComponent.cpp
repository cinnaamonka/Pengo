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
		m_LifesAmount(3),
		m_Speed(30.0f),
		m_DestTextureRect{},
		m_CanCollisionBeChecked(false)
	{

	}

	void ActorComponent::Damage(int damage)
	{
		m_LifesAmount -= damage;

		m_LifesAmountChanged.CreateMessage(m_LifesAmount);

		m_StateChanged.CreateMessage(GameEngine::State::PlayerDied);
	}
}
