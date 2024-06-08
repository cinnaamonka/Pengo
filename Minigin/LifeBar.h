#pragma once
#include <memory>
#include "GameObject.h"

#include <glm/glm.hpp>

namespace GameEngine
{
	class LifeBarFactory final
	{
	public:
		LifeBarFactory() = default;
		~LifeBarFactory() = default;

		LifeBarFactory(const LifeBarFactory& other) = delete;
		LifeBarFactory& operator=(const LifeBarFactory& other) = delete;
		LifeBarFactory(LifeBarFactory&& other) noexcept = delete;
		LifeBarFactory& operator=(LifeBarFactory&& other) noexcept = delete;

		static std::unique_ptr<GameEngine::GameObject> CreateLifeIcon(const glm::vec3& position);
	};

}