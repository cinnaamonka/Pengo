#include "Game.h"

#include <InputManager.h>
#include <InputCommands.h>

#include <StatesAndTransitions.h>
#include "HitObserver.h"
#include "BlockComponent.h"
#include "PengoInputCommands.h"

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

void Game::Initialize()
{
	auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("Demo");

	m_pPengoActor = std::make_unique<PengoActor>();
	auto hitObserverComponent = m_pPengoActor->GetHitObserver();

	m_pEnvironment = std::make_unique<GameEngine::GameObject>();
	m_pEnvironment->AddComponent<Environment>("Level.json", &scene);
	m_pEnvironment->GetComponent<Environment>()->SetActor(m_pPengoActor->GetReferenceToActor());
	m_pEnvironment->GetComponent<Environment>()->AttachObserver<GameEngine::HitInfo>(hitObserverComponent);
	
	m_pEnvironmentReference = m_pEnvironment.get();

	scene.Add(std::move(m_pEnvironment));
	scene.Add(std::move(m_pPengoActor->GetActorGameObject()));

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

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_A, GameEngine::InputState::Previous },
		std::make_unique<PushBlockCommand>(m_pEnvironmentReference));

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

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_SPACE, GameEngine::InputState::Previous },
		std::make_unique<PushBlockCommand>(m_pEnvironmentReference));

	input.AddCommand<GameEngine::Keyboard>( 
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_SPACE, GameEngine::InputState::Previous }, 
		std::make_unique<GameEngine::PushCommand>(gameActor)); 
}