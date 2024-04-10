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

		const float GetSpeed()
		{
			return m_Speed;
		}

		void SetSpeed(float speed)
		{
			m_Speed = speed;
		}
		void AttachScoreObserver(IObserver<int>* pObserver);
		void AttachLifesObserver(IObserver<int>* pObserver);
		void AttachStateObserver(IObserver<State>* pObserver);

	private:

		int m_Score;
		int m_LifesAmount;
		float m_Speed;

		Subject<int> m_ScoreChanged;
		Subject<int> m_LifesAmountChanged;
		Subject<State> m_StateChanged;

	};
}


