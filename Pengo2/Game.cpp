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
#include <ActorComponent.h>


#include <SoundSystem.h>
#include <SoundServiceLocator.h>
#include <SoundLogSystem.h>
#include <TimeManager.h>


#include <HUD.h>
#include <thread>

#include "Structs.h"

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <SDL_mixer.h>

//#include <vld.h>
bool Game::m_IsLevelComplete = false;
std::mutex Game::m_CallbackMutex;

void Game::Initialize(int levelIndex,int maxLevelsAmount)
{
	GameEngine::TimeManager::StopAllTimers();


	const std::string levelName = "Level" + std::to_string(levelIndex) + ".json";

	GameEngine::LevelInfo levelInfo{};

	// Load level blocks
	GameEngine::GetLevelInfo(levelName, levelInfo);

	m_CurrentLevelIndex = levelIndex;
	m_MaxLevelsCount = maxLevelsAmount;

	auto& scene = GameEngine::SceneManager::GetInstance().CreateScene(levelName);

	m_pPengoActor = std::make_unique<PengoActor>(m_FirstPlayerPosition);
	m_pEggsObserver = std::make_unique<EggObserver>(&scene);
	m_pScoreObserver = std::make_unique<ScoreObserver>(&scene);

	auto hitObserverComponent = m_pPengoActor->GetHitObserver();
	m_pPengoActor->GetActorGameObject()->GetComponent<GameEngine::ActorComponent>()->AttachObserver(this);

	m_pEnvironment = std::make_unique<GameEngine::GameObject>();
	m_pEnvironment->AddComponent<Environment>(levelInfo.levelBlocks, &scene);
	m_pEnvironment->AddComponent<EnvironmentObserver>();
	m_pEnvironment->GetComponent<Environment>()->SetActor(m_pPengoActor->GetReferenceToActor());

	if (levelInfo.gameMode == GameEngine::GameModes::Versus)
	{
		m_SecondPlayerPosition = levelInfo.enemiesPositions.back();
		levelInfo.enemiesPositions.erase(levelInfo.enemiesPositions.end() - 1);

		m_pEnemyManager = std::make_unique<EnemyManager>(static_cast<int>(levelInfo.enemiesPositions.size()), levelInfo.enemiesPositions, &scene,
			m_pPengoActor->GetReferenceToActor());
	}
	else
	{
		m_pEnemyManager = std::make_unique<EnemyManager>(static_cast<int>(levelInfo.enemiesPositions.size()), levelInfo.enemiesPositions, &scene,
			m_pPengoActor->GetReferenceToActor());
		m_pEnemyManager->AddPlayer(m_pPengoActor->GetReferenceToActor());
	}
	

	m_pEnvironment->GetComponent<Environment>()->SetEnemyManager(m_pEnemyManager.get());
	m_pEnvironment->GetComponent<Environment>()->AttachObserver<GameEngine::HitInfo>(hitObserverComponent);
	m_pEnvironment->GetComponent<Environment>()->AttachObserver<glm::vec3>(m_pEggsObserver.get());
	m_pEnvironment->GetComponent<Environment>()->AttachObserver<EventInfo>(m_pEnvironment->GetComponent<EnvironmentObserver>());
	m_pEnvironment->GetComponent<Environment>()->AttachObserver<Score>(m_pScoreObserver.get());

	m_pEnvironmentReference = m_pEnvironment.get();

	scene.Add(std::move(m_pEnvironment));
	scene.Add(std::move(m_pPengoActor->GetActorGameObject()));

	m_pPengoActor->GetReferenceToActor()->GetComponent<GameEngine::ActorComponent>()->SetLives(levelInfo.lifesAmount);

	switch (levelInfo.gameMode)
	{
	case GameEngine::GameModes::Co_op:
	{
		m_pSecondPengoActor = std::make_unique<PengoActor>(m_SecondPlayerPosition);

		auto co_opPengoHitObserver = m_pSecondPengoActor->GetHitObserver();
		m_pSecondPengoActor->GetActorGameObject()->GetComponent<GameEngine::ActorComponent>()->AttachObserver(this);
		m_pEnvironmentReference->GetComponent<Environment>()->SetActor(m_pSecondPengoActor->GetReferenceToActor());
		m_pEnemyManager->AddPlayer(m_pSecondPengoActor->GetReferenceToActor());
		scene.Add(std::move(m_pSecondPengoActor->GetActorGameObject()));
		InitializeInputSystem(m_pSecondPengoActor->GetReferenceToActor(),GameEngine::GameModes::Co_op,1);
		m_pSecondPengoActor->GetReferenceToActor()->GetComponent<GameEngine::ActorComponent>()->SetLives(levelInfo.lifesAmount);
		m_pEnvironmentReference->GetComponent<Environment>()->AttachObserver(co_opPengoHitObserver);
		break;
	}
	case GameEngine::GameModes::SinglePlayer:
		InitializeInputSystem(m_pPengoActor->GetReferenceToActor(), GameEngine::GameModes::SinglePlayer,0);
		break;
	case GameEngine::GameModes::Versus:
	{
		m_SecondPlayerPosition.y -= 20;

		auto pengoActorEnemy = PengoActor::CreateControlledPengoEnemy(m_SecondPlayerPosition);

		pengoActorEnemy->GetComponent<EnemyActor>()->HandleInput(&EnemyManager::enemyPatrolState); 
		pengoActorEnemy->GetComponent<EnemyActor>()->SetActor(m_pPengoActor->GetReferenceToActor());

		auto versusPengoHitObserver = pengoActorEnemy->GetComponent<HitObserver>();

		InitializeInputSystem(pengoActorEnemy.get(), GameEngine::GameModes::Versus, 1);

		m_pEnvironmentReference->GetComponent<Environment>()->AttachObserver(versusPengoHitObserver); 
		m_pEnvironmentReference->GetComponent<Environment>()->SetPlayerEnemy(pengoActorEnemy.get()); 

		m_pEnemyManager->AddPlayer(m_pPengoActor->GetReferenceToActor());  
		m_pEnemyManager->SetPlayerEnemy(pengoActorEnemy.get());
		scene.Add(std::move(pengoActorEnemy));
		break;
	}
	default:
		break;
	}

	//initialize HUD
	m_pHUD = std::make_unique<GameEngine::HUD>();
	m_pHUD->AddScoreBar(levelInfo.hudPositions["ScoreBar"], &scene,levelInfo.score);
	m_pHUD->CreateGameMode(levelInfo.hudPositions["GameMode"], &scene, levelInfo.gameMode);
	m_pHUD->CreateSnoBeesBar(levelInfo.hudPositions["SnoBeesBar"], 3, &scene);
	m_pHUD->AddLifeBar(levelInfo.hudPositions["LifeBar"], &scene, levelInfo.lifesAmount);

	m_pEnvironmentReference->GetComponent<Environment>()->AttachObserver<GameEngine::HUDEvent>(m_pHUD.get());

	//Sounds start one after another
	GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().Play(static_cast<int>(PengoSounds::ActStarts), 20);

	Mix_ChannelFinished(SoundCallback);

}

bool Game::IsLevelComplete()
{
	return m_IsLevelComplete;
}

void Game::Notify(const GameEngine::State& messageFromSubject)
{
	int lifes = m_pPengoActor->GetReferenceToActor()->GetComponent<GameEngine::ActorComponent>()->GetLives();
	const std::string& levelName = "Level" + std::to_string(m_CurrentLevelIndex + 1) + ".json";
	const std::string& scoreFileName = "Score.json";

	switch (messageFromSubject)
	{
	case GameEngine::State::PlayerDied:
		GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().Play(static_cast<int>(PengoSounds::PlayerDeath), 20);


		Mix_ChannelFinished([](int)
			{
				m_IsLevelComplete = true;
				Mix_ChannelFinished(nullptr);
			});

		while (GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().IsPlaying(static_cast<int>(PengoSounds::ActStarts)))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		
		GameEngine::UpdateLevelFile("lifesAmount", lifes, levelName);
		GameEngine::UpdateLevelFile("scoreAmount", m_pHUD->GetScore(), levelName);

		if (m_CurrentLevelIndex == m_MaxLevelsCount - 1)
		{
			GameEngine::UpdateLevelFile("score", m_pHUD->GetScore(), scoreFileName);
		}

		break;
	case GameEngine::State::Victory:

		GameEngine::UpdateLevelFile("lifesAmount", lifes - 1,levelName);
		GameEngine::UpdateLevelFile("scoreAmount", m_pHUD->GetScore(),levelName);

		if (m_CurrentLevelIndex == m_MaxLevelsCount - 1)
		{
			GameEngine::UpdateLevelFile("score", m_pHUD->GetScore(), scoreFileName);
		}

		GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().Stop(static_cast<int>(PengoSounds::Background));

		m_IsLevelComplete = true;
		break;
	}

}

void Game::InitializeInputSystem(GameEngine::GameObject* gameActor, GameEngine::GameModes currentGameMode,int deviceIndex)
{
	auto& input = GameEngine::InputManager::GetInstance();

	input.CleanUp();

    switch (currentGameMode)
    {
    case GameEngine::GameModes::SinglePlayer:
    {
		//ADD CONTROLLER AND KEYBOARD
		InitializeSinglePlayerInput(input, gameActor, deviceIndex);

        break;
    }
    case GameEngine::GameModes::Co_op:
    {
		InitializeSinglePlayerController(input, m_pPengoActor->GetReferenceToActor(), 0);
		InitializeSinglePlayerController(input, m_pSecondPengoActor->GetReferenceToActor(), 1);
		InitializeSinglePlayerKeyboard(input, m_pSecondPengoActor->GetReferenceToActor());
        break;
    }
    case GameEngine::GameModes::Versus:
		InitializeSinglePlayerController(input, m_pPengoActor->GetReferenceToActor(), 0);
		InitializeVersusPlayerEnemyController(input, gameActor, deviceIndex); 
		InitializeVersusPlayerEnemyKeyboard(input, gameActor, deviceIndex);
		
        break;
    default:
        break;
    }
	
    input.AddCommand<GameEngine::Keyboard>(
        GameEngine::InputKeyboardBinding{ SDL_SCANCODE_F1, GameEngine::InputState::Released,0 },
        std::make_unique<SkipLevelCommand>(gameActor, std::bind(&Game::SkipLevel, this)));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_F6, GameEngine::InputState::Released,0 },
		std::make_unique<MuteSoundCommand>(gameActor));
}

void Game::LoadSounds()
{
	auto& soundSystem = GameEngine::SoundServiceLocator::GetSoundSystemInstance();

	for (const auto& [soundType, filePath] : SOUND_PATH_MAPPING)
	{
		soundSystem.Load(filePath, static_cast<GameEngine::sound_id>(static_cast<int>(soundType)));
	}
}

void Game::InitializeSinglePlayerInput(GameEngine::InputManager& input,GameEngine::GameObject* gameActor, int deviceIndex)
{
	//ADD CONTROLLER AND KEYBOARD
	
	InitializeSinglePlayerKeyboard(input, gameActor); 
	InitializeSinglePlayerController(input, gameActor, deviceIndex);
}

void Game::InitializeSinglePlayerKeyboard(GameEngine::InputManager& input, GameEngine::GameObject* gameActor)
{
	auto m_Keyboard = std::make_unique<GameEngine::Keyboard>();
	input.AddDevice(std::move(m_Keyboard));

	//Keyboard movement
	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_A, GameEngine::InputState::Previous,0 },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ -1,0, 0 }));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_D, GameEngine::InputState::Previous,0 },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 1,0, 0 }));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_W, GameEngine::InputState::Previous,0 },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0,-1, 0 }));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_S, GameEngine::InputState::Previous,0 },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0,1, 0 }));

	//stop collision check
	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_A, GameEngine::InputState::Released,0 },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_D, GameEngine::InputState::Released,0 },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_W, GameEngine::InputState::Released,0 },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_S, GameEngine::InputState::Released,0 },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));


	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_SPACE, GameEngine::InputState::Previous,0 },
		std::make_unique<PushBlockCommand>(m_pEnvironmentReference,gameActor));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_SPACE, GameEngine::InputState::Released,0 },
		std::make_unique<StopPushCommand>(m_pEnvironmentReference));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_SPACE, GameEngine::InputState::Previous,0 },
		std::make_unique<GameEngine::PushCommand>(gameActor));
}

void Game::InitializeSinglePlayerController(GameEngine::InputManager& input, GameEngine::GameObject* gameActor, int deviceIndex)
{
	auto m_Controller = std::make_unique<GameEngine::Controller>(deviceIndex);
	input.AddDevice(std::move(m_Controller));

	//Movement
	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_LEFT, GameEngine::InputState::Previous,deviceIndex },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ -1, 0, 0 }));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_RIGHT, GameEngine::InputState::Previous,deviceIndex },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 1, 0, 0 }));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_UP, GameEngine::InputState::Previous,deviceIndex },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0, -1, 0 }));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_DOWN, GameEngine::InputState::Previous,deviceIndex },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0, 1, 0 }));

	//Stop collision check
	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_LEFT, GameEngine::InputState::Released,deviceIndex },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_RIGHT, GameEngine::InputState::Released,deviceIndex },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_UP, GameEngine::InputState::Released,deviceIndex },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_DOWN, GameEngine::InputState::Released,deviceIndex },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));


	//push
	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_A, GameEngine::InputState::Previous,deviceIndex },
		std::make_unique<PushBlockCommand>(m_pEnvironmentReference,gameActor));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_A, GameEngine::InputState::Released,deviceIndex },
		std::make_unique<StopPushCommand>(m_pEnvironmentReference));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_A, GameEngine::InputState::Previous,deviceIndex },
		std::make_unique<GameEngine::PushCommand>(gameActor));
}

void Game::InitializeVersusPlayerEnemyController(GameEngine::InputManager& input, GameEngine::GameObject* gameActor, int deviceIndex)
{
	auto m_Controller = std::make_unique<GameEngine::Controller>(deviceIndex);
	input.AddDevice(std::move(m_Controller));

	//Movement
	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_LEFT, GameEngine::InputState::Previous,deviceIndex },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ -1, 0, 0 }));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_RIGHT, GameEngine::InputState::Previous,deviceIndex },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 1, 0, 0 }));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_UP, GameEngine::InputState::Previous,deviceIndex },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0, -1, 0 }));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_DOWN, GameEngine::InputState::Previous,deviceIndex },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0, 1, 0 }));

	//Stop collision check
	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_LEFT, GameEngine::InputState::Released,deviceIndex },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_RIGHT, GameEngine::InputState::Released,deviceIndex },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_UP, GameEngine::InputState::Released,deviceIndex },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_DOWN, GameEngine::InputState::Released,deviceIndex },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));


	//push
	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_A, GameEngine::InputState::Previous,deviceIndex },
		std::make_unique<BreakBlockCommand>(m_pEnvironmentReference));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_A, GameEngine::InputState::Released,deviceIndex },
		std::make_unique<StopPushCommand>(m_pEnvironmentReference));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_A, GameEngine::InputState::Previous,deviceIndex },
		std::make_unique<GameEngine::PushCommand>(gameActor)); 
}

void Game::InitializeVersusPlayerEnemyKeyboard(GameEngine::InputManager& input, GameEngine::GameObject* gameActor, int)
{
	auto m_Keyboard = std::make_unique<GameEngine::Keyboard>(); 
	input.AddDevice(std::move(m_Keyboard)); 

	//Keyboard movement
	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_A, GameEngine::InputState::Previous,0 }, 
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ -1,0, 0 })); 

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_D, GameEngine::InputState::Previous,0 }, 
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 1,0, 0 }));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_W, GameEngine::InputState::Previous,0 },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0,-1, 0 }));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_S, GameEngine::InputState::Previous,0 },
		std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0,1, 0 }));

	//stop collision check
	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_A, GameEngine::InputState::Released,0 },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_D, GameEngine::InputState::Released,0 },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_W, GameEngine::InputState::Released,0 },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_S, GameEngine::InputState::Released,0 },
		std::make_unique<GameEngine::StopCollisionCheck>(gameActor));


	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_SPACE, GameEngine::InputState::Previous,0 },
		std::make_unique<BreakBlockCommand>(m_pEnvironmentReference));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_SPACE, GameEngine::InputState::Released,0 },
		std::make_unique<StopPushCommand>(m_pEnvironmentReference));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_SPACE, GameEngine::InputState::Previous,0 },
		std::make_unique<GameEngine::PushCommand>(gameActor));
}


void Game::SkipLevel()
{
	GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().Stop(static_cast<int>(PengoSounds::Background));
	m_IsLevelComplete = true;
}

void Game::SoundCallback(int)
{
	std::lock_guard<std::mutex> lock(m_CallbackMutex);
	GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().Play(static_cast<int>(PengoSounds::Background), 20);
	Mix_ChannelFinished(nullptr);
}

