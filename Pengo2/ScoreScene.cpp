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

	pEnterYourInitials->AddComponent<GameEngine::TransformComponent>(glm::vec3{ 170,100,0 });
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

	m_pStaticLetterState = std::make_unique<StaticLetterState>();
	m_pFlyckeringLetterState = std::make_unique<FlyckeringLetterState>();
	m_pShouldStartFlyckering = std::make_unique<ShouldStartFlyckering>();

	AddLetter(glm::vec3{ 400,200,0 },&scene);
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

void ScoreScene::InitializeInputSystem(GameEngine::GameObject*)
{

}
