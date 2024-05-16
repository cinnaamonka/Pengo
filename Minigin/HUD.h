#pragma once
#include "BaseComponent.h"

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

#include <memory>


namespace GameEngine
{
	class Scene;
	class GameObject;

	class HUD final
	{
	public:
		HUD() = default;
		~HUD() = default;

		HUD(const HUD& other) = delete;
		HUD& operator=(const HUD& other) = delete;
		HUD(HUD&& other) noexcept = delete;
		HUD& operator=(HUD&& other) noexcept = delete;

		void AddScoreBar(const glm::vec3& position,Scene* scene);
	private:
		GameEngine::GameObject* m_pScoreBar;
	};

}

