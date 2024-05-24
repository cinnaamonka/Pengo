#pragma once
#include "BaseComponent.h"
#include "IObserver.h"

namespace GameEngine
{
	enum class State;

	class HealthObserver final: public BaseComponent, public IObserver<State>
	{
	public:
		HealthObserver(GameObject* pGameObject);
		~HealthObserver() = default;

		HealthObserver(const HealthObserver& other) = delete;
		HealthObserver& operator=(const HealthObserver& other) = delete;
		HealthObserver(HealthObserver&& other) noexcept = delete;
		HealthObserver& operator=(HealthObserver&& other) noexcept = delete;

		void Notify(const State& messageFromSubject) override;
	};
};


