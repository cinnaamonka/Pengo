#include "ScoreScene.h"
#include <SceneManager.h>
#include <TransformComponent.h>
#include <TextComponent.h>
#include <ResourceManager.h>
#include <RenderComponent.h>
#include <AnimationComponent.h>
#include <memory>

void ScoreScene::Initialize(int score) 
{
	auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("ScoreScene");

	std::unique_ptr<GameEngine::GameObject> pEnterYourInitials = std::make_unique<GameEngine::GameObject>();

	auto bigFont = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);
	auto middleFont = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);

	pEnterYourInitials->AddComponent<GameEngine::TransformComponent>(glm::vec3{170,100,0});
	pEnterYourInitials->AddComponent<GameEngine::TextComponent>("ENTER YOUR INITIALS", bigFont);
	pEnterYourInitials->AddComponent<GameEngine::AnimationComponent>();
	pEnterYourInitials->AddComponent<GameEngine::RenderComponent>();
	scene.Add(std::move(pEnterYourInitials));

	std::unique_ptr<GameEngine::GameObject> pFinalScoreText = std::make_unique<GameEngine::GameObject>();
	pFinalScoreText->AddComponent<GameEngine::TransformComponent>(glm::vec3{ 150,150,0 });
	pFinalScoreText->AddComponent<GameEngine::TextComponent>("SCORE", middleFont);
	pFinalScoreText->AddComponent<GameEngine::AnimationComponent>();
	pFinalScoreText->AddComponent<GameEngine::RenderComponent>();
	scene.Add(std::move(pFinalScoreText)); 

	std::unique_ptr<GameEngine::GameObject> pName = std::make_unique<GameEngine::GameObject>();
	pName->AddComponent<GameEngine::TransformComponent>(glm::vec3{ 400,150,0 });
	pName->AddComponent<GameEngine::TextComponent>("NAME", middleFont);
	pName->AddComponent<GameEngine::AnimationComponent>();
	pName->AddComponent<GameEngine::RenderComponent>();
	scene.Add(std::move(pName));

	std::unique_ptr<GameEngine::GameObject> pCurrentScore = std::make_unique<GameEngine::GameObject>();
	pCurrentScore->AddComponent<GameEngine::TransformComponent>(glm::vec3{ 160,200,0 });
	pCurrentScore->AddComponent<GameEngine::TextComponent>(std::to_string(score), middleFont);
	pCurrentScore->AddComponent<GameEngine::AnimationComponent>();
	pCurrentScore->AddComponent<GameEngine::RenderComponent>();
	scene.Add(std::move(pCurrentScore));
}

void ScoreScene::InitializeInputSystem(GameEngine::GameObject*)
{

}
