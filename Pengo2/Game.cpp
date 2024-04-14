#include "Game.h"

#include <InputManager.h>
#include <InputCommands.h>

#include <StatesAndTransitions.h>
#include "CollisionObserver.h"
#include "HitObserver.h"

void Game::Initialize()
{
	auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("Demo");

	m_pPengoActor = std::make_unique<PengoActor>();

	auto collisionObserverComponent = m_pPengoActor->GetCollisionObserver();
	auto hitObserverComponent = m_pPengoActor->GetHitObserver();
	scene.Add(std::move(m_pPengoActor->GetActorGameObject()));

	m_pEnvironment = std::make_unique<GameEngine::GameObject>();
	m_pEnvironment->AddComponent<Environment>("Level.json", &scene);
	m_pEnvironment->GetComponent<Environment>()->SetActor(m_pPengoActor->GetReferenceToActor());

	m_pEnvironment->GetComponent<Environment>()->AttachObserver<GameEngine::CollisionState>(collisionObserverComponent);
	m_pEnvironment->GetComponent<Environment>()->AttachObserver<GameEngine::HitInfo>(hitObserverComponent); 

	scene.Add(std::move(m_pEnvironment));

	InitializeInputSystem(m_pPengoActor->GetReferenceToActor());
}

void Game::InitializeInputSystem(GameEngine::GameObject* gameActor)
{
	auto& input = GameEngine::InputManager::GetInstance();
	auto m_Controller = std::make_unique<GameEngine::Controller>(0);
	auto m_Keyboard = std::make_unique<GameEngine::Keyboard>();
	input.AddDevice(std::move(m_Controller));
	input.AddDevice(std::move(m_Keyboard));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_LEFT, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ -1, 0, 0 }));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_RIGHT, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 1, 0, 0 }));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_UP, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0, -1, 0 }));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_DOWN, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0, 1, 0 }));

	//Keyboard Input
	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_A, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ -1,0, 0 }));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_D, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 1,0, 0 }));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_W, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0,-1, 0 }));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_S, GameEngine::InputState::Previous },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0,1, 0 }));
}