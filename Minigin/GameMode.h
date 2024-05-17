#pragma once
#include <memory>
#include "GameObject.h"

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "Helpers.h"

namespace GameEngine
{
	class GameMode
	{
	public:
		GameMode() = default;
		~GameMode() = default;

		GameMode(const GameMode& other) = delete;
		GameMode& operator=(const GameMode& other) = delete;
		GameMode(GameMode&& other) noexcept = delete;
		GameMode& operator=(GameMode&& other) noexcept = delete;

		static std::unique_ptr<GameEngine::GameObject> CreateGameMode(const glm::vec3& position,GameModes gameMode);

	private:

	};

}

