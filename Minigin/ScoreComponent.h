#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace GameEngine
{
	class ScoreComponent : public BaseComponent
	{
	public:

		ScoreComponent(GameObject* pGameObject);
		~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;

		void AddScore(int amount);

		int GetScore() const
		{
			return m_Score;
		}

		int SetScore(int score)
		{
			m_Score = score;
		}

	private:
		int m_Score;

	};
}

