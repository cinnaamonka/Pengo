#include "ScoreBar.h"
#include "TransformComponent.h"
#include "RenderComponent.h"
#include "AnimationComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"

std::unique_ptr<GameEngine::GameObject> GameEngine::ScoreBarFactory::CreateScoreBar(const glm::vec3& position, int currentScore)
{
	std::unique_ptr<GameEngine::GameObject> gameObject = std::make_unique<GameEngine::GameObject>();


	auto font = GameEngine::ResourceManager::GetInstance().GetFont(GameEngine::FontTypes::Middle); 

	std::string scoreStrBefore = std::to_string(currentScore);
	int digitsBefore = static_cast<int>(scoreStrBefore.length());

	int shiftPerDigit = 10;
	glm::vec3 pos = position;
	pos.x -= (digitsBefore - 1) * shiftPerDigit;


	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(static_cast<int>(pos.x), static_cast<int>(pos.y), 0));
	gameObject->AddComponent<GameEngine::TextComponent>(std::to_string(currentScore), font);
	gameObject->AddComponent<GameEngine::AnimationComponent>();
	gameObject->AddComponent<GameEngine::RenderComponent>();

	return gameObject;
}
