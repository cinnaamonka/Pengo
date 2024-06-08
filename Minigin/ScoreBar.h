#pragma once
#include "BaseComponent.h"

#include <glm/glm.hpp>

namespace GameEngine
{ 
	class ScoreBarFactory final
	{
	public:
		ScoreBarFactory() = default;
		~ScoreBarFactory() = default;

		ScoreBarFactory(const ScoreBarFactory& other) = delete;
		ScoreBarFactory& operator=(const ScoreBarFactory& other) = delete;
		ScoreBarFactory(ScoreBarFactory&& other) noexcept = delete;
		ScoreBarFactory& operator=(ScoreBarFactory&& other) noexcept = delete;

		static std::unique_ptr<GameEngine::GameObject> CreateScoreBar(const glm::vec3& position,int currentScore);

	};

}