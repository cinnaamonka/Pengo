#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace GameEngine
{
	class GameObject;
	class ScoreObserver;
	class HealthObserver;

	enum class State
	{
		PlayerDied
	};

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
				// Attach to m_StateChanged when T is State
				m_StateChanged.Attach(pObserver);
			}
			else if constexpr (std::is_same_v<T, int>)
			{

				m_LifesAmountChanged.Attach(pObserver);
				m_ScoreChanged.Attach(pObserver);
			}
		}

	private:

		int m_Score;
		int m_LifesAmount;
		float m_Speed;

		Subject<int> m_ScoreChanged;
		Subject<int> m_LifesAmountChanged;
		Subject<State> m_StateChanged;

	};
}


