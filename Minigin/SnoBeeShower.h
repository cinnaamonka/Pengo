#pragma once
#include "BaseComponent.h"

#include <glm/glm.hpp>


namespace GameEngine
{
	class SnoBeeShower final
	{
	public:
		SnoBeeShower() = default;
		~SnoBeeShower() = default;

		SnoBeeShower(const SnoBeeShower& other) = delete;
		SnoBeeShower& operator=(const SnoBeeShower& other) = delete;
		SnoBeeShower(SnoBeeShower&& other) noexcept = delete;
		SnoBeeShower& operator=(SnoBeeShower&& other) noexcept = delete;
		
		static std::unique_ptr<GameEngine::GameObject> CreateSnoBeesBar(const glm::vec3& position);

	};

}
