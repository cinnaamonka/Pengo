#include "Engine.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "RotationComponent.h"
#include "ImGuiComponent.h"
#include "InputCommands.h"
#include "BaseCommand.h"
#include "InputManager.h"
#include "LivesComponent.h"
#include "ScoreComponent.h"
#include "Observers.h"
#include "FPS.h"

#include "Scene.h"

void load()
{
	auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("Demo");

	// Game object background
	auto gameObject = std::make_unique<GameEngine::GameObject>();

	// transform component to background
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(0, 0, 0));

	// texture component to background
	gameObject->AddComponent<GameEngine::TextureComponent>("background.tga");

	// render component to background
	gameObject->AddComponent<GameEngine::RenderComponent>();

	scene.Add(std::move(gameObject));

	// game object DAELabel
	gameObject = std::make_unique<GameEngine::GameObject>();
	// transform component to DAELabel
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(216, 180, 0));
	// add texture component to DAELabel
	gameObject->AddComponent<GameEngine::TextureComponent>("logo.tga");
	// add render component to DAELAbel
	gameObject->AddComponent<GameEngine::RenderComponent>();

	scene.Add(std::move(gameObject));

	// add text object 
	auto font = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	gameObject = std::make_unique<GameEngine::GameObject>();

	// add transform component to this game object
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(170, 20, 0));

	// add text component 
	gameObject->AddComponent<GameEngine::TextComponent>("Programming 4 Assignment", font);

	// add render component
	gameObject->AddComponent<GameEngine::RenderComponent>();

	scene.Add(std::move(gameObject));

	// add fps game object
	gameObject = std::make_unique<GameEngine::GameObject>();

	//add transform component
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(20, 20, 0));
	
	// add text component 
	gameObject->AddComponent<GameEngine::TextComponent>("FPS", font);

	// add fps component
	gameObject->AddComponent<GameEngine::FPS>();

	// add render component
	gameObject->AddComponent<GameEngine::RenderComponent>();

	scene.Add(std::move(gameObject));

	//TODO: ADD POSSIBILITY TO LOAD PNG
	//Add a rotating character
	auto rotatingCharacterPengo = std::make_unique<GameEngine::GameObject>();

	rotatingCharacterPengo->AddComponent<GameEngine::TransformComponent>(glm::vec3(300, 350, 0));
	rotatingCharacterPengo->AddComponent<GameEngine::TextureComponent>("Pengo.tga");
//	rotatingCharacterPengo->AddComponent<GameEngine::RotationComponent>(40, 100);
	rotatingCharacterPengo->AddComponent<GameEngine::RenderComponent>();

    GameEngine::GameObject* referenceToRotatingCharacterPengo = rotatingCharacterPengo.get();

	scene.Add(std::move(rotatingCharacterPengo));

	auto secondRotatingCharacterPengo = std::make_unique<GameEngine::GameObject>();
	secondRotatingCharacterPengo->AddComponent<GameEngine::TransformComponent>(glm::vec3(200, 350, 0));
	secondRotatingCharacterPengo->AddComponent<GameEngine::TextureComponent>("Pengo.tga");
	//secondRotatingCharacterPengo->AddComponent<GameEngine::RotationComponent>(40, 100);
	secondRotatingCharacterPengo->AddComponent<GameEngine::RenderComponent>();
	//secondRotatingCharacterPengo->SetParent(referenceToRotatingCharacterPengo);

	GameEngine::GameObject* referenceToRotatingSecondCharacterPengo = secondRotatingCharacterPengo.get();

	scene.Add(std::move(secondRotatingCharacterPengo));

	auto ImGuiObject = std::make_unique<GameEngine::GameObject>();
	ImGuiObject->AddComponent<GameEngine::ImGuiComponent>();
	
	ImGuiObject->SetParent(std::move(ImGuiObject.get()));

	scene.Add(std::move(ImGuiObject));

	auto& input = GameEngine::InputManager::GetInstance();
	auto m_Controller = std::make_unique<GameEngine::Controller>(0);
	auto m_Keyboard = std::make_unique<GameEngine::Keyboard>();

	input.AddDevice(std::move(m_Controller));
	input.AddDevice(std::move(m_Keyboard));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_LEFT, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingCharacterPengo,glm::vec3{ -1, 0, 0 },30.0f));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_RIGHT, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingCharacterPengo,glm::vec3{ 1, 0, 0 },30.0f));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_UP, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingCharacterPengo,glm::vec3{ 0, -1, 0 },30.0f));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_DOWN, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingCharacterPengo,glm::vec3{ 0, 1, 0 },30.0f));

	//Keyboard Input
	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_A, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingSecondCharacterPengo,glm::vec3{ -1,0, 0 },30.0f));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_D, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingSecondCharacterPengo,glm::vec3{ 1,0, 0 },30.0f));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_W, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingSecondCharacterPengo,glm::vec3{ 0,-1, 0 },30.0f));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_S, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingSecondCharacterPengo,glm::vec3{ 0,1, 0 },30.0f));


	auto smallFont = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	gameObject = std::make_unique<GameEngine::GameObject>();
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(50, 80, 0));
	gameObject->AddComponent<GameEngine::TextComponent>("Use WASD to move second character, Z to to pick up pellets", smallFont);
	gameObject->AddComponent<GameEngine::RenderComponent>();
	scene.Add(std::move(gameObject));

	//score 
	gameObject = std::make_unique<GameEngine::GameObject>();
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(50, 110, 0));
	gameObject->AddComponent<GameEngine::ScoreComponent>();
	const int score = gameObject->GetComponent<GameEngine::ScoreComponent>()->GetScore();
	gameObject->AddComponent<GameEngine::TextComponent>("# score: " + std::to_string(score), smallFont);
	gameObject->AddComponent<GameEngine::RenderComponent>();

	auto scoreComponent = gameObject->GetComponent<GameEngine::ScoreComponent>();
	auto textComponent = gameObject->GetComponent<GameEngine::TextComponent>();
	scoreComponent->Attach(textComponent);

	GameEngine::GameObject* referenceToSecondScoreText = gameObject.get();

	scene.Add(std::move(gameObject));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_Z, GameEngine::InputState::Pressed
		},
		std::make_unique<GameEngine::ScoreCommand>(referenceToSecondScoreText, 10));

	//gameObject = std::make_unique<GameEngine::GameObject>();
	//gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(50, 95, 0));
	//gameObject->AddComponent<GameEngine::LivesComponent>();

	//const int lifes = gameObject->GetComponent<GameEngine::LivesComponent>()->GetLives();

	//gameObject->AddComponent<GameEngine::TextComponent>("# Lifes: " + std::to_string(lifes), smallFont);
	//gameObject->AddComponent<GameEngine::RenderComponent>();

	//scene.Add(std::move(gameObject));


}

int main(int, char* []) 
{
	GameEngine::Engine engine("../Data/");
	engine.Run(load);
	return 0;
}