#include "Game.h"

#include <InputManager.h>
#include <ResourceManager.h>
#include <InputCommands.h>

#include "HitObserver.h"
#include "EggObserver.h"

#include "EnvironmentObserver.h"
#include "BlockComponent.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "PengoInputCommands.h"

#include <SoundSystem.h>
#include <SoundServiceLocator.h>
#include <SoundLogSystem.h>

#include <HUD.h>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

//#include <vld.h>

void Game::Initialize()
{
	auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("Demo");

	m_EnemiesPositions.push_back(glm::vec3{ 400, 280, 0 });
	m_EnemiesPositions.push_back(glm::vec3{ 280, 140, 0 });
	m_EnemiesPositions.push_back(glm::vec3{ 340, 140, 0 });

	m_pPengoActor             = std::make_unique<PengoActor>();
	m_pEggsObserver           = std::make_unique<EggObserver>(&scene); 
	m_pScoreObserver          = std::make_unique<ScoreObserver>(&scene);

	auto hitObserverComponent = m_pPengoActor->GetHitObserver();

	m_pEnvironment = std::make_unique<GameEngine::GameObject>();
	m_pEnvironment->AddComponent<Environment>("Level.json", &scene);
	m_pEnvironment->AddComponent<EnvironmentObserver>(); 
	m_pEnvironment->GetComponent<Environment>()->SetActor(m_pPengoActor->GetReferenceToActor());

	m_pEnemyManager = std::make_unique<EnemyManager>(static_cast<int>(m_EnemiesPositions.size()), m_EnemiesPositions, &scene, 
		m_pPengoActor->GetReferenceToActor());

	m_pEnvironment->GetComponent<Environment>()->SetEnemyManager(m_pEnemyManager.get()); 
	m_pEnvironment->GetComponent<Environment>()->AttachObserver<GameEngine::HitInfo>(hitObserverComponent);
	m_pEnvironment->GetComponent<Environment>()->AttachObserver<glm::vec3>(m_pEggsObserver.get());
	m_pEnvironment->GetComponent<Environment>()->AttachObserver<EventInfo>(m_pEnvironment->GetComponent<EnvironmentObserver>());
	m_pEnvironment->GetComponent<Environment>()->AttachObserver<Score>(m_pScoreObserver.get());
	
	m_pEnvironmentReference = m_pEnvironment.get();

	scene.Add(std::move(m_pEnvironment));
	scene.Add(std::move(m_pPengoActor->GetActorGameObject()));

	InitializeInputSystem(m_pPengoActor->GetReferenceToActor());

	GameEngine::SoundServiceLocator::RegisterSoundSystem(std::make_unique<GameEngine::SoundLogSystem>
		(std::make_unique<GameEngine::SoundSystem>()));

	//initialize HUD
	m_pHUD = std::make_unique<GameEngine::HUD>();
	m_pHUD->AddScoreBar(glm::vec3{ 270,10,0 }, &scene);
	m_pHUD->AddLifeBar(glm::vec3{ 180,35,0 }, &scene,2);
	m_pHUD->CreateGameMode(glm::vec3{ 200,10,0 }, &scene,GameEngine::GameModes::SinglePlayer);
	m_pHUD->CreateSnoBeesBar(glm::vec3{ 400,40,0 }, &scene, 3);

	m_pEnvironmentReference->GetComponent<Environment>()->AttachObserver<GameEngine::HUDEvent>(m_pHUD.get()); 
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

	//Keyboard Input
	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_A, GameEngine::InputState::Released },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_D, GameEngine::InputState::Released },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_W, GameEngine::InputState::Released },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_S, GameEngine::InputState::Released },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));



	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_SPACE, GameEngine::InputState::Previous },
		std::make_unique<PushBlockCommand>(m_pEnvironmentReference));

	input.AddCommand<GameEngine::Keyboard>( 
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_SPACE, GameEngine::InputState::Previous }, 
		std::make_unique<GameEngine::PushCommand>(gameActor)); 
}