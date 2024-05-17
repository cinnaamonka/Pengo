#pragma once
#include "BaseComponent.h"

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

#include <memory>
#include "IObserver.h"

namespace GameEngine
{
	class Scene;
	class GameObject;

	enum class HUDEvent
	{

	};

	class HUD final : public IObserver<HUDEvent>, public IObserver<int>
	{
	public:
		HUD() = default;
		~HUD() = default;

		HUD(const HUD& other) = delete;
		HUD& operator=(const HUD& other) = delete;
		HUD(HUD&& other) noexcept = delete;
		HUD& operator=(HUD&& other) noexcept = delete;

		void AddScoreBar(const glm::vec3& position,Scene* scene);
		void Notify(const HUDEvent& messageFromSubject) override;
		void Notify(const int& messageFromSubject) override; 
	private:
		GameEngine::GameObject* m_pScoreBar;

		int m_Score = 0;
	};

}

