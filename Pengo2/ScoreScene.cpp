#include "ScoreScene.h"
#include <SceneManager.h>
#include <TransformComponent.h>
#include <TextComponent.h>
#include <ResourceManager.h>
#include <RenderComponent.h>
#include <AnimationComponent.h>
#include <TextureComponent.h>
#include <Texture2D.h>

#include <memory>

void ScoreScene::Initialize(int score)
{
	auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("ScoreScene");

	std::unique_ptr<GameEngine::GameObject> pEnterYourInitials = std::make_unique<GameEngine::GameObject>();

	auto bigFont = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);
	auto middleFont = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);

	AddText(glm::vec3{ 150,150,0 }, "SCORE", &scene, bigFont);
	AddText(glm::vec3{ 170,100,0 }, "ENTER YOUR INITIALS", &scene, bigFont);
	AddText(glm::vec3{ 400,150,0 }, "NAME", &scene, middleFont);
	AddText(glm::vec3{ 160,200,0 }, std::to_string(score), &scene, middleFont);

	m_pStaticLetterState = std::make_unique<StaticLetterState>();
	m_pFlyckeringLetterState = std::make_unique<FlyckeringLetterState>();
	m_pShouldStartFlyckering = std::make_unique<ShouldStartFlyckering>();

	AddLetter(glm::vec3{ 400,200,0 }, &scene);
}

void ScoreScene::AddLetter(const glm::vec3& position, GameEngine::Scene* scene)
{
	std::unique_ptr<GameEngine::GameObject> pFirstLetter = std::make_unique<GameEngine::GameObject>();
	pFirstLetter->AddComponent<GameEngine::TransformComponent>(position);
	pFirstLetter->AddComponent<GameEngine::TextureComponent>("LetterA.tga");
	pFirstLetter->AddComponent<GameEngine::AnimationComponent>();
	pFirstLetter->AddComponent<GameEngine::RenderComponent>();

	auto textureSizeX = pFirstLetter->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / 2;
	auto textureSizeY = pFirstLetter->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y;

	pFirstLetter->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });

	pFirstLetter->AddComponent<GameEngine::FSM>(m_pStaticLetterState.get(), pFirstLetter->GetComponent<GameEngine::AnimationComponent>());
	pFirstLetter->GetComponent<GameEngine::FSM>()->AddTransition(m_pStaticLetterState.get(), m_pFlyckeringLetterState.get(), m_pShouldStartFlyckering.get());

	scene->Add(std::move(pFirstLetter));
}

void ScoreScene::AddText(const glm::vec3& position, const std::string& text, GameEngine::Scene* scene, std::shared_ptr<GameEngine::Font> font)
{
	std::unique_ptr<GameEngine::GameObject> pFinalScoreText = std::make_unique<GameEngine::GameObject>();
	pFinalScoreText->AddComponent<GameEngine::TransformComponent>(position); 
	pFinalScoreText->AddComponent<GameEngine::TextComponent>(text, font);
	pFinalScoreText->AddComponent<GameEngine::AnimationComponent>();
	pFinalScoreText->AddComponent<GameEngine::RenderComponent>();
	scene->Add(std::move(pFinalScoreText));
}

void ScoreScene::InitializeInputSystem(GameEngine::GameObject*)
{

}
