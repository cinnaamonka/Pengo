#include "ScoreScene.h"
#include <SceneManager.h>
#include <TransformComponent.h>
#include <TextComponent.h>
#include <ResourceManager.h>
#include <RenderComponent.h>
#include <AnimationComponent.h>
#include <TextureComponent.h>
#include <Texture2D.h>
#include <InputManager.h>
#include <TimeManager.h>
#include "ScoreSceneCommands.h"

#include <memory>

void ScoreScene::Initialize(int score)
{
	GameEngine::TimeManager::StopAllTimers();

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

	auto firstLetterA = AddLetter(glm::vec3{ 400,200,0 });

	InitializeInputSystem(firstLetterA.get());

	scene.Add(std::move(firstLetterA));
}
	

std::unique_ptr<GameEngine::GameObject> ScoreScene::AddLetter(const glm::vec3& position)
{
	std::unique_ptr<GameEngine::GameObject> pFirstLetter = std::make_unique<GameEngine::GameObject>();
	pFirstLetter->AddComponent<GameEngine::TransformComponent>(position);
	pFirstLetter->AddComponent<GameEngine::TextureComponent>("Alphabet.tga");
	pFirstLetter->AddComponent<GameEngine::AnimationComponent>();
	pFirstLetter->AddComponent<GameEngine::RenderComponent>();

	auto textureSizeX = pFirstLetter->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / 16;
	auto textureSizeY = pFirstLetter->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y/ 4;

	pFirstLetter->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });

	pFirstLetter->AddComponent<GameEngine::FSM>(m_pStaticLetterState.get(), pFirstLetter->GetComponent<GameEngine::AnimationComponent>());
	pFirstLetter->GetComponent<GameEngine::FSM>()->AddTransition(m_pStaticLetterState.get(), m_pFlyckeringLetterState.get(), m_pShouldStartFlyckering.get());

	pFirstLetter->GetComponent<GameEngine::AnimationComponent>()->SetHorizontalOffset(1);
	pFirstLetter->GetComponent<GameEngine::AnimationComponent>()->SetVerticalOffset(0);

	return pFirstLetter;
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

void ScoreScene::InitializeInputSystem(GameEngine::GameObject* gameActor)
{
	auto& input = GameEngine::InputManager::GetInstance();

	input.CleanUp();

	auto m_Controller = std::make_unique<GameEngine::Controller>(0);
	auto m_Keyboard = std::make_unique<GameEngine::Keyboard>();
	input.AddDevice(std::move(m_Controller));
	input.AddDevice(std::move(m_Keyboard));

	//Keyboard Input
	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_RIGHT, GameEngine::InputState::Released },
		std::make_unique<ChangeLetterCommand>(gameActor));

}
