#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "Helpers.h"

namespace GameEngine
{
	class GameObject;
	class ScoreObserver;

	class ActorComponent final: public BaseComponent
	{
	public:

		ActorComponent(GameObject* pGameObject);
		~ActorComponent() = default;
		ActorComponent(const ActorComponent& other) = delete;
		ActorComponent& operator=(const ActorComponent& other) = delete;
		ActorComponent(ActorComponent&& other) = delete;

		void Damage(int damage);
		void Win();

		int GetLives() const
		{
			return m_LifesAmount;
		}

		void SetLives(int lives)
		{
			m_LifesAmount = lives;
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

		const Rect& GetDestTextureRect() const
		{
			return m_DestTextureRect;
		}

		const int GetScore() const 
		{
			return m_Score;
		}
		
		void SetScore(int score) 
		{
			m_Score = score;
		}

	private:
		int m_LifesAmount;
		int m_Score;

		bool m_CanCollisionBeChecked;

		float m_Speed;
		
		Rect m_DestTextureRect;

		Subject<int> m_LifesAmountChanged;
		Subject<GameEngine::State> m_StateChanged;



	};
}


