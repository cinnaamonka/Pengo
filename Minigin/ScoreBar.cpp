#include "ScoreBar.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "AnimationComponent.h"
#include "TextComponent.h"
#include "Texture2D.h"


std::unique_ptr<GameEngine::GameObject> GameEngine::ScoreBarFactory::CreateScoreBar(const glm::vec3& position)
{
	std::unique_ptr<GameEngine::GameObject> gameObject = std::make_unique<GameEngine::GameObject>();

	auto font = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(static_cast<int>(position.x), static_cast<int>(position.y), 0));
	gameObject->AddComponent<GameEngine::TextComponent>("0", font);
	gameObject->AddComponent<GameEngine::AnimationComponent>();
	gameObject->AddComponent<GameEngine::RenderComponent>();

	return gameObject;
}
