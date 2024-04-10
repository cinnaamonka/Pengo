#include "Game.h"

#include "InputManager.h"
#include "InputCommands.h"

#include <TransformComponent.h>
#include <TextureComponent.h>
#include <RenderComponent.h>
#include <BoxColliderComponent.h>

void Game::Initialize()
{
    auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("Demo");

    m_pActor = std::make_unique<GameEngine::GameObject>();
    m_pActor->AddComponent<GameEngine::TransformComponent>(glm::vec3(300, 350, 0));
    m_pActor->AddComponent<GameEngine::TextureComponent>("Pengo.tga");
    m_pActor->AddComponent<GameEngine::RenderComponent>();
    m_pActor->AddComponent<GameEngine::BoxCollider>(300,350,20,20); 
    GameEngine::GameObject* referenceToCharacterPengo = m_pActor.get();
    scene.Add(std::move(m_pActor));

    InitializeInputSystem(referenceToCharacterPengo);
    m_pEnvironment = std::make_unique<Environment>("Level.json",&scene); 
}

void Game::Update()
{
    glm::vec2 speed = { 5,4 };
    m_pEnvironment->CheckCollision(m_pActor->GetComponent<GameEngine::BoxCollider>()->GetBoxCollider(), speed); 
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
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ -1, 0, 0 }, 30.0f));

    input.AddCommand<GameEngine::Controller>(
        GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_RIGHT, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 1, 0, 0 }, 30.0f));

    input.AddCommand<GameEngine::Controller>(
        GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_UP, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0, -1, 0 }, 30.0f));

    input.AddCommand<GameEngine::Controller>(
        GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_GAMEPAD_DRAD_DOWN, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0, 1, 0 }, 30.0f));

    //Keyboard Input
    input.AddCommand<GameEngine::Keyboard>(
        GameEngine::InputKeyboardBinding{ SDL_SCANCODE_A, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ -1,0, 0 }, 30.0f));

    input.AddCommand<GameEngine::Keyboard>(
        GameEngine::InputKeyboardBinding{ SDL_SCANCODE_D, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 1,0, 0 }, 30.0f));

    input.AddCommand<GameEngine::Keyboard>(
        GameEngine::InputKeyboardBinding{ SDL_SCANCODE_W, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0,-1, 0 }, 30.0f));

    input.AddCommand<GameEngine::Keyboard>(
        GameEngine::InputKeyboardBinding{ SDL_SCANCODE_S, GameEngine::InputState::Previous },
        std::make_unique<GameEngine::MoveCommand>(gameActor, glm::vec3{ 0,1, 0 }, 30.0f));
}