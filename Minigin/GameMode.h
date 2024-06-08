#pragma once
#include <memory>
#include "GameObject.h"
#include "Helpers.h"
#include <glm/glm.hpp>

namespace GameEngine
{
	class GameMode final
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

