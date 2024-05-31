#include "StartScreen.h"
#include <SceneManager.h>
#include <TransformComponent.h>
#include <TextureComponent.h>
#include <TextComponent.h>
#include <RenderComponent.h>
#include <ResourceManager.h>
#include <InputManager.h>
#include "StartSceneCommands.h"

void StartScreen::Initialize()
{
	auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("StartScene");
	auto font = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	AddPicture("PengoLogo.tga", m_LabelPosition, &scene);
	AddText("SinglePlayer", m_SinglePlayerPosition, &scene, font);
	AddPicture("AButton.tga", m_AButton, &scene);
	AddText("Co-Op", m_Co_OpPosition, &scene, font);
	AddPicture("BButton.tga", m_BButton, &scene);
	AddText("Versus", m_VSPosition, &scene, font);
	AddPicture("XButton.tga", m_XButton, &scene);

	m_pInputGameObject = std::make_unique<GameEngine::GameObject>();
	scene.Add(std::move(m_pInputGameObject));

	InitializeInputSystem(m_pInputGameObject.get(),GameEngine::GameModes::Co_op);
}

void StartScreen::InitializeInputSystem(GameEngine::GameObject* gameObject, GameEngine::GameModes,int deviceIndex)
{
	auto& input = GameEngine::InputManager::GetInstance(); 

	auto m_Controller = std::make_unique<GameEngine::Controller>(deviceIndex);
	auto m_Keyboard = std::make_unique<GameEngine::Keyboard>();
	input.AddDevice(std::move(m_Controller));
	input.AddDevice(std::move(m_Keyboard));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_F1, GameEngine::InputState::Released },
		std::make_unique<ChooseSinglePlayer>(gameObject, std::bind(&StartScreen::CompleteLevel, this)));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_F2, GameEngine::InputState::Released },
		std::make_unique<ChooseCoOp>(gameObject, std::bind(&StartScreen::CompleteLevel, this)));
}

void StartScreen::AddPicture(const std::string& texturePath, const glm::vec3& position, GameEngine::Scene* scene)
{
	std::unique_ptr<GameEngine::GameObject> pButtonX = std::make_unique<GameEngine::GameObject>(); 
	pButtonX->AddComponent<GameEngine::TransformComponent>(position);
	pButtonX->AddComponent<GameEngine::TextureComponent>(texturePath);
	pButtonX->AddComponent<GameEngine::AnimationComponent>(); 
	pButtonX->AddComponent<GameEngine::RenderComponent>(); 

	scene->Add(std::move(pButtonX));
}

void StartScreen::AddText(const std::string& text, const glm::vec3& position, GameEngine::Scene* scene,std::shared_ptr<GameEngine::Font> font)
{
	std::unique_ptr<GameEngine::GameObject> pVersus = std::make_unique<GameEngine::GameObject>();
	pVersus->AddComponent<GameEngine::TransformComponent>(position);
	pVersus->AddComponent<GameEngine::TextComponent>(text, font); 
	pVersus->AddComponent<GameEngine::AnimationComponent>();
	pVersus->AddComponent<GameEngine::RenderComponent>();

	scene->Add(std::move(pVersus));
}
