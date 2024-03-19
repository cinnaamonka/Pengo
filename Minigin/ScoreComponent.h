#pragma once
#include "BaseComponent.h"

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

		void AddPoints(int amount);

		int GetScore() const { return m_Score; }

		Event<int> ScoreChanged;


	private:
		// Member variables
		int m_Score{ 0 };

	};
}


