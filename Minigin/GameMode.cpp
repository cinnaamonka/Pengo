#include "GameMode.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "AnimationComponent.h"

std::unique_ptr<GameEngine::GameObject> GameEngine::GameMode::CreateGameMode(const glm::vec3& position, GameModes gameMode)
{
	std::unique_ptr<GameEngine::GameObject> gameObject = std::make_unique<GameEngine::GameObject>();

	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(static_cast<int>(position.x), static_cast<int>(position.y + 5), 0));

	switch (gameMode)
	{
		case GameModes::SinglePlayer:
			gameObject->AddComponent<GameEngine::TextureComponent>("1.tga");
			break;
	}

	gameObject->AddComponent<GameEngine::AnimationComponent>();
	gameObject->AddComponent<GameEngine::RenderComponent>();

	return gameObject;
}
