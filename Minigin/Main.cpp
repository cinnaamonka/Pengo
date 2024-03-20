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
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "FPS.h"

#include "Scene.h"

void load()
{
	auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("Demo");

	
	auto gameObject = std::make_unique<GameEngine::GameObject>();
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(0, 0, 0));
	gameObject->AddComponent<GameEngine::TextureComponent>("background.tga");
	gameObject->AddComponent<GameEngine::RenderComponent>();
	scene.Add(std::move(gameObject));

	
	gameObject = std::make_unique<GameEngine::GameObject>();
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(216, 180, 0));
	gameObject->AddComponent<GameEngine::TextureComponent>("logo.tga");
	gameObject->AddComponent<GameEngine::RenderComponent>();
	scene.Add(std::move(gameObject));

	
	auto font = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	gameObject = std::make_unique<GameEngine::GameObject>();
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(170, 20, 0));
	gameObject->AddComponent<GameEngine::TextComponent>("Programming 4 Assignment", font);
	gameObject->AddComponent<GameEngine::RenderComponent>();
	scene.Add(std::move(gameObject));

	
	gameObject = std::make_unique<GameEngine::GameObject>();
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(20, 20, 0));
	gameObject->AddComponent<GameEngine::TextComponent>("FPS", font);
	gameObject->AddComponent<GameEngine::FPS>();
	gameObject->AddComponent<GameEngine::RenderComponent>();
	scene.Add(std::move(gameObject));


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
	gameObject->AddComponent<GameEngine::TextComponent>("Use WASD to move second character,C to inflict damage, Z and X to to pick up pellets", smallFont);
	gameObject->AddComponent<GameEngine::RenderComponent>();
	scene.Add(std::move(gameObject));

	gameObject = std::make_unique<GameEngine::GameObject>();
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(50, 60, 0));
	gameObject->AddComponent<GameEngine::TextComponent>("Use D-Pad to move first character,X to inflict damage, A and B to to pick up pellets", smallFont);
	gameObject->AddComponent<GameEngine::RenderComponent>();
	scene.Add(std::move(gameObject));

	//score 
	gameObject = std::make_unique<GameEngine::GameObject>();
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(50, 140, 0));
	gameObject->AddComponent<GameEngine::ScoreComponent>();
	const int score = gameObject->GetComponent<GameEngine::ScoreComponent>()->GetScore();
	gameObject->AddComponent<GameEngine::TextComponent>("# Score: " + std::to_string(score), smallFont);
	gameObject->AddComponent<GameEngine::RenderComponent>();

	auto scoreComponent = gameObject->GetComponent<GameEngine::ScoreComponent>();
	auto textComponent = gameObject->GetComponent<GameEngine::TextComponent>();
	textComponent->AddAdditionalText("# Score: ");
	//observer pattern 
	scoreComponent->Attach(textComponent);
	GameEngine::GameObject* referenceToSecondScoreText = gameObject.get();
	scene.Add(std::move(gameObject));

	//score 
	gameObject = std::make_unique<GameEngine::GameObject>();
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(50, 100, 0));
	gameObject->AddComponent<GameEngine::ScoreComponent>();
	const int scoreFirstCharacter = gameObject->GetComponent<GameEngine::ScoreComponent>()->GetScore();
	gameObject->AddComponent<GameEngine::TextComponent>("# Score: " + std::to_string(scoreFirstCharacter), smallFont);
	gameObject->AddComponent<GameEngine::RenderComponent>();

	auto scoreComponentFirstCharacter = gameObject->GetComponent<GameEngine::ScoreComponent>();
	auto textComponentFirstCharacter = gameObject->GetComponent<GameEngine::TextComponent>();
	textComponentFirstCharacter->AddAdditionalText("# Score: ");
	//observer pattern 
	scoreComponentFirstCharacter->Attach(textComponentFirstCharacter);
	GameEngine::GameObject* referenceToFirstScoreText = gameObject.get();
	scene.Add(std::move(gameObject));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_Z, GameEngine::InputState::Pressed
		},
		std::make_unique<GameEngine::ScoreCommand>(referenceToSecondScoreText, 10));


	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_X, GameEngine::InputState::Pressed
		},
		std::make_unique<GameEngine::ScoreCommand>(referenceToSecondScoreText, 100));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_A, GameEngine::InputState::Pressed
		},
		std::make_unique<GameEngine::ScoreCommand>(referenceToFirstScoreText, 10));


	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_B, GameEngine::InputState::Pressed
		},
		std::make_unique<GameEngine::ScoreCommand>(referenceToFirstScoreText, 100));

	
	
	gameObject = std::make_unique<GameEngine::GameObject>();
	GameEngine::GameObject* referenceToSecondLifesText = gameObject.get();
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(50, 125, 0));
	gameObject->AddComponent<GameEngine::HealthComponent>();
	const auto lifesComponent = gameObject->GetComponent<GameEngine::HealthComponent>();

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_C, GameEngine::InputState::Pressed
		},
		std::make_unique<GameEngine::LifesCommand>(referenceToSecondLifesText, 1));

	gameObject->AddComponent<GameEngine::TextComponent>("# Lifes: " + std::to_string(lifesComponent->GetLives()), smallFont);
	auto textComponentLifesObject = gameObject->GetComponent<GameEngine::TextComponent>();
	textComponentLifesObject->AddAdditionalText("# Lifes: ");
	lifesComponent->Subject<int>::Attach(textComponentLifesObject);
	lifesComponent->Subject<std::string>::Attach(textComponentLifesObject);
	gameObject->AddComponent<GameEngine::RenderComponent>();
	scene.Add(std::move(gameObject));


	gameObject = std::make_unique<GameEngine::GameObject>();
	GameEngine::GameObject* referenceToFirstHealthText = gameObject.get();
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(50, 90, 0));
	gameObject->AddComponent<GameEngine::HealthComponent>();
	const auto healthComponentFirstCharacter = gameObject->GetComponent<GameEngine::HealthComponent>();

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_X, GameEngine::InputState::Pressed
		},
		std::make_unique<GameEngine::LifesCommand>(referenceToFirstHealthText, 1));

	gameObject->AddComponent<GameEngine::TextComponent>("# Lifes: " + std::to_string(healthComponentFirstCharacter->GetLives()), smallFont);
	auto textComponentHealthFirstCharacter = gameObject->GetComponent<GameEngine::TextComponent>();
	textComponentHealthFirstCharacter->AddAdditionalText("# Lifes: ");
	healthComponentFirstCharacter->Subject<int>::Attach(textComponentHealthFirstCharacter);
	healthComponentFirstCharacter->Subject<std::string>::Attach(textComponentHealthFirstCharacter);
	gameObject->AddComponent<GameEngine::RenderComponent>();
	scene.Add(std::move(gameObject));


}

int main(int, char* []) 
{
	GameEngine::Engine engine("../Data/");
	engine.Run(load);
	return 0;
}