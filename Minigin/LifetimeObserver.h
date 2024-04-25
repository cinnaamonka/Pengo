#pragma once
#include "BaseComponent.h"
#include "IObserver.h"
#include "Helpers.h"

namespace GameEngine
{
	class LifetimeObserver : public GameEngine::BaseComponent, public GameEngine::IObserver<bool>
	{
	public:

		LifetimeObserver(GameEngine::GameObject* pGameObject);
		~LifetimeObserver() = default;
		LifetimeObserver(const LifetimeObserver& other) = delete;
		LifetimeObserver& operator=(const LifetimeObserver& other) = delete;
		LifetimeObserver(LifetimeObserver&& other) = delete;

		void Notify(const bool& message_from_subject) override;
	};

}

