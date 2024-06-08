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

	GameEngine::ResourceManager::GetInstance().LoadFontFromFile(GameEngine::FontTypes::Small, "Lingua.otf", 12); 
	GameEngine::ResourceManager::GetInstance().LoadFontFromFile(GameEngine::FontTypes::Middle, "Lingua.otf", 16);
	GameEngine::ResourceManager::GetInstance().LoadFontFromFile(GameEngine::FontTypes::Big, "Lingua.otf", 28);

	auto font = GameEngine::ResourceManager::GetInstance().GetFont(GameEngine::FontTypes::Middle); 

	AddPicture("PengoLogo.tga", m_LabelPosition, &scene);
	AddText("SinglePlayer", m_SinglePlayerPosition, &scene, font);
	AddPicture("AButton.tga", m_AButton, &scene);
	AddText("Co-Op", m_Co_OpPosition, &scene, font);
	AddPicture("BButton.tga", m_BButton, &scene);
	AddText("Versus", m_VSPosition, &scene, font);
	AddPicture("XButton.tga", m_XButton, &scene);
	AddText("Press F6 to mute sound", m_MuteButtonPosition, &scene, font);
	AddText("WASD on keyboard to move,space to push", m_KeyboardMovementInstructionPosition, &scene, font);
	AddText("F1 to skip", m_SkipLevelPosition, &scene, font);

	AddText("F2", m_SinglePlayerPositionLabel, &scene, font);
	AddText("F3", m_CoOpPositionLabel, &scene, font);
	AddText("F4", m_VsPositionLabel, &scene, font);

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
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_F2, GameEngine::InputState::Released },
		std::make_unique<ChooseSinglePlayer>(gameObject, std::bind(&StartScreen::CompleteLevel, this)));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_F3, GameEngine::InputState::Released },
		std::make_unique<ChooseCoOp>(gameObject, std::bind(&StartScreen::CompleteLevel, this)));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_F4, GameEngine::InputState::Released }, 
		std::make_unique<ChooseVersus>(gameObject, std::bind(&StartScreen::CompleteLevel, this)));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_A, GameEngine::InputState::Released,deviceIndex },
		std::make_unique<ChooseSinglePlayer>(gameObject, std::bind(&StartScreen::CompleteLevel, this)));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_B, GameEngine::InputState::Released,deviceIndex },
		std::make_unique<ChooseCoOp>(gameObject, std::bind(&StartScreen::CompleteLevel, this)));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_X, GameEngine::InputState::Released,deviceIndex },
		std::make_unique<ChooseVersus>(gameObject, std::bind(&StartScreen::CompleteLevel, this)));
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
