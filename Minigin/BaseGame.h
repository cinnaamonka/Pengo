#pragma once

namespace GameEngine
{
	class GameObject;

	class BaseGame
	{
	public:
		BaseGame() = default;
		BaseGame(const BaseGame& other) = delete;
		BaseGame& operator=(const BaseGame& other) = delete;
		BaseGame(BaseGame&& other) = delete;
		BaseGame& operator=(BaseGame&& other) = delete;
		virtual ~BaseGame() {};

		virtual void InitializeInputSystem(GameEngine::GameObject* gameActor) = 0;
		virtual bool IsLevelComplete() = 0;
		virtual void ResetLevel() = 0;
	};
}


