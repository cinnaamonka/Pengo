#include "LivesComponent.h"
namespace GameEngine
{
	LivesComponent::LivesComponent(GameObject* pGameObject) :BaseComponent(pGameObject), m_NrLives(3)
	{
		
	}
	void LivesComponent::Kill()
	{
		m_NrLives--;

		if (m_NrLives <= 0)
		{
			GetGameObject()->OnNotify(GameEngine::Event::PlayerDeath);
		}
		else
		{
			GetGameObject()->OnNotify(GameEngine::Event::DecreaseLifesAmount);
		}
		
	}
}