#include "HealthComponent.h"
namespace GameEngine
{
	HealthComponent::HealthComponent(GameObject* pGameObject) 
		:BaseComponent(pGameObject), 
		m_NrLives(3)
	{
		
	}
	void HealthComponent::Damage(int damage)
	{
		m_NrLives -= damage;

		Subject<int>::CreateMessage(m_NrLives);

		if (m_NrLives <= 0)
		{
			Subject<std::string>::CreateMessage("Player died!");
		}
		
	}
}