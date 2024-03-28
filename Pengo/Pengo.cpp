#include <Engine.h>

#include "ResourceManager.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "RotationComponent.h"
#include "ImGuiComponent.h"
#include "InputCommands.h"
#include "BaseCommand.h"
#include "InputManager.h"
#include "ActorComponent.h"
#include "ScoreObserver.h"
#include "HealthObserver.h"
#include "FPS.h"
#include "iostream"
#include "Scene.h" 
#include "SceneManager.h" 
#include "GameObject.h" 


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
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingCharacterPengo, glm::vec3{ -1, 0, 0 }, 30.0f));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_RIGHT, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingCharacterPengo, glm::vec3{ 1, 0, 0 }, 30.0f));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_UP, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingCharacterPengo, glm::vec3{ 0, -1, 0 }, 30.0f));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_DOWN, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingCharacterPengo, glm::vec3{ 0, 1, 0 }, 30.0f));

	//Keyboard Input
	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_A, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingSecondCharacterPengo, glm::vec3{ -1,0, 0 }, 30.0f));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_D, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingSecondCharacterPengo, glm::vec3{ 1,0, 0 }, 30.0f));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_W, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingSecondCharacterPengo, glm::vec3{ 0,-1, 0 }, 30.0f));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_S, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(referenceToRotatingSecondCharacterPengo, glm::vec3{ 0,1, 0 }, 30.0f));


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
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(50, 130, 0));
	gameObject->AddComponent<GameEngine::ActorComponent>();
	auto actorComponentFirstCharacter = gameObject->GetComponent<GameEngine::ActorComponent>();
	gameObject->AddComponent<GameEngine::TextComponent>("# Score: " + std::to_string(actorComponentFirstCharacter->GetScore()), smallFont);
	gameObject->AddComponent<GameEngine::RenderComponent>();
	gameObject->AddComponent<GameEngine::ScoreObserver>();

	auto textComponentFirstCharacter = gameObject->GetComponent<GameEngine::TextComponent>();
	auto scoreObserverFirstScoreText = gameObject->GetComponent<GameEngine::ScoreObserver>();

	textComponentFirstCharacter->AddAdditionalText("# Score: ");
	//observer pattern 
	actorComponentFirstCharacter->AttachScoreObserver(scoreObserverFirstScoreText);
	GameEngine::GameObject* referenceToFirstScoreText = gameObject.get();
	scene.Add(std::move(gameObject));

	//score 
	gameObject = std::make_unique<GameEngine::GameObject>();
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(50, 100, 0));
	gameObject->AddComponent<GameEngine::ActorComponent>();
	auto actorComponentSecondCharacter = gameObject->GetComponent<GameEngine::ActorComponent>();
	gameObject->AddComponent<GameEngine::TextComponent>("# Score: " + std::to_string(actorComponentSecondCharacter->GetScore()), smallFont);
	gameObject->AddComponent<GameEngine::RenderComponent>();
	gameObject->AddComponent<GameEngine::ScoreObserver>();

	auto textComponentSecondCharacter = gameObject->GetComponent<GameEngine::TextComponent>();
	auto scoreObserverSecondScoreText = gameObject->GetComponent<GameEngine::ScoreObserver>();

	textComponentSecondCharacter->AddAdditionalText("# Score: ");
	//observer pattern 
	actorComponentSecondCharacter->AttachScoreObserver(scoreObserverSecondScoreText);
	GameEngine::GameObject* referenceToSecondScoreText = gameObject.get();
	scene.Add(std::move(gameObject));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_Z, GameEngine::InputState::Pressed
		},
		std::make_unique<GameEngine::ScoreCommand>(referenceToFirstScoreText, 10));


	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_X, GameEngine::InputState::Pressed
		},
		std::make_unique<GameEngine::ScoreCommand>(referenceToFirstScoreText, 100));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_A, GameEngine::InputState::Pressed
		},
		std::make_unique<GameEngine::ScoreCommand>(referenceToSecondScoreText, 10));


	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_B, GameEngine::InputState::Pressed
		},
		std::make_unique<GameEngine::ScoreCommand>(referenceToSecondScoreText, 100));

	//HEALTH

	gameObject = std::make_unique<GameEngine::GameObject>();
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(50, 115, 0));
	gameObject->AddComponent<GameEngine::ActorComponent>();
	auto actorComponentFirstLifesText = gameObject->GetComponent<GameEngine::ActorComponent>();
	gameObject->AddComponent<GameEngine::TextComponent>("# Lifes: " + std::to_string(actorComponentFirstLifesText->GetLives()), smallFont);
	gameObject->AddComponent<GameEngine::RenderComponent>();
	gameObject->AddComponent<GameEngine::HealthObserver>();

	auto textComponentFirstLifesText = gameObject->GetComponent<GameEngine::TextComponent>();
	auto lifesObserverFirstLifesText = gameObject->GetComponent<GameEngine::HealthObserver>();

	textComponentFirstLifesText->AddAdditionalText("# Lifes: ");
	actorComponentFirstLifesText->AttachLifesObserver(lifesObserverFirstLifesText);
	actorComponentFirstLifesText->AttachStateObserver(lifesObserverFirstLifesText);
	GameEngine::GameObject* referenceToFirstLifesText = gameObject.get();
	scene.Add(std::move(gameObject));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_X, GameEngine::InputState::Pressed
		},
		std::make_unique<GameEngine::LifesCommand>(referenceToFirstLifesText, 1));


	gameObject = std::make_unique<GameEngine::GameObject>();
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(50, 140, 0));
	gameObject->AddComponent<GameEngine::ActorComponent>();
	auto actorComponentSecondLifesText = gameObject->GetComponent<GameEngine::ActorComponent>();
	gameObject->AddComponent<GameEngine::TextComponent>("# Lifes: " + std::to_string(actorComponentSecondLifesText->GetLives()), smallFont);
	gameObject->AddComponent<GameEngine::RenderComponent>();
	gameObject->AddComponent<GameEngine::HealthObserver>();

	GameEngine::TextComponent* textComponentSecondLifesText = gameObject->GetComponent<GameEngine::TextComponent>();
	GameEngine::HealthObserver* lifesObserverSecondLifesText = gameObject->GetComponent<GameEngine::HealthObserver>();

	textComponentSecondLifesText->AddAdditionalText("# Lifes: ");
	actorComponentSecondLifesText->AttachLifesObserver(lifesObserverSecondLifesText);
	actorComponentSecondLifesText->AttachStateObserver(lifesObserverSecondLifesText);
	GameEngine::GameObject* referenceToSecondLifesText = gameObject.get();
	scene.Add(std::move(gameObject));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_C, GameEngine::InputState::Pressed
		},
		std::make_unique<GameEngine::LifesCommand>(referenceToSecondLifesText, 1));



}

int main(int, char* [])
{

	GameEngine::Engine engine("../Data/");
	engine.Run(load);

	return 0;
}
