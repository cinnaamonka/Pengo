#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace GameEngine
{

	class HealthComponent final: public BaseComponent, public Subject<int>, public Subject<std::string>
	{
	public:
		HealthComponent(GameObject* pGameObject);
		~HealthComponent() = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) noexcept = delete;
		HealthComponent& operator=(HealthComponent&& other) noexcept = delete;

		void Damage(int damage);

		int GetLives() const
		{ 
			return m_NrLives; 
		}


	private:
		int m_NrLives;
	};
};


