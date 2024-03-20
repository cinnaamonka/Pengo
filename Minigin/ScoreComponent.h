#pragma once
#include "BaseComponent.h"
#include "Subject.h"

#include <memory>
namespace GameEngine
{
	class ScoreComponent final: public BaseComponent
	{
	public:

		ScoreComponent(GameObject* pGameObject);
		~ScoreComponent() = default;
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;

		void AddScore(int score);
		void RemoveScore(int score);

		int GetScore() const
		{
			return m_Score;
		}
		

	private:
		int m_Score;

		std::unique_ptr<GameEngine::Subject<ScoreComponent>> OnScoreChange;
	

	};
}

