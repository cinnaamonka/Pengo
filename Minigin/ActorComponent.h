#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "Helpers.h"
#include "HealthObserver.h"

namespace GameEngine
{
	class GameObject;
	class ScoreObserver;

	class ActorComponent : public BaseComponent
	{
	public:

		ActorComponent(GameObject* pGameObject);
		~ActorComponent() = default;
		ActorComponent(const ActorComponent& other) = delete;
		ActorComponent& operator=(const ActorComponent& other) = delete;
		ActorComponent(ActorComponent&& other) = delete;

		void AddScore(int score);
		void RemoveScore(int score);

		void Damage(int damage);

		int GetLives() const
		{
			return m_LifesAmount;
		}

		int GetScore() const
		{
			return m_Score;
		}

		const float GetSpeed() const
		{
			return m_Speed;
		}

		void SetSpeed(float speed)
		{
			m_Speed = speed;
		}
		template<typename T>
		void AttachObserver(IObserver<T>* pObserver)
		{
			if constexpr (std::is_same_v<T, State>)
			{
				m_StateChanged.Attach(pObserver);
			}
			else if constexpr (std::is_same_v<T, int>)
			{
				m_LifesAmountChanged.Attach(pObserver);
				m_ScoreChanged.Attach(pObserver);
			}
		}
		void SetCollisionCanBeChecked(bool canBeChecked)
		{
			m_CanCollisionBeChecked = canBeChecked;
		}

		const bool GetCollisionBeChecked()const
		{
			return m_CanCollisionBeChecked;
		}

		const Rect& GetDestTextureRect()
		{
			return m_DestTextureRect;
		}


	private:

		int m_Score;
		int m_LifesAmount;

		bool m_CanCollisionBeChecked;

		float m_Speed;
	
		Rect m_DestTextureRect;

		Subject<int> m_ScoreChanged;
		Subject<int> m_LifesAmountChanged;
		Subject<GameEngine::State> m_StateChanged;

	};
}


