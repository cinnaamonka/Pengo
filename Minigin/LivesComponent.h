#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace GameEngine
{
	class LivesComponent : public BaseComponent
	{
	public:
		LivesComponent(GameObject* pGameObject);
		~LivesComponent() = default;

		// Copy and Move semantics
		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) noexcept = delete;
		LivesComponent& operator=(LivesComponent&& other) noexcept = delete;

		void Kill();

		int GetLives() const
		{ 
			return m_NrLives; 
		}


	private:
		int m_NrLives;
	};
};


