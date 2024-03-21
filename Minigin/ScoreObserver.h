#pragma once
#include "BaseComponent.h"
#include "IObserver.h"

#include <memory>
namespace GameEngine
{
	class ScoreObserver final : public BaseComponent, public IObserver<int>
	{
	public:

		ScoreObserver(GameObject* pGameObject);
		~ScoreObserver() = default;
		ScoreObserver(const ScoreObserver& other) = delete;
		ScoreObserver& operator=(const ScoreObserver& other) = delete;
		ScoreObserver(ScoreObserver&& other) = delete;

		void Notify(const int& message_from_subject) override;

	};
}

