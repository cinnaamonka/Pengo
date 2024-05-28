#include "Letter.h"
#include <TransformComponent.h>
#include <TextureComponent.h>
#include <AnimationComponent.h>
#include <RenderComponent.h>
#include <Texture2D.h>
#include <InputManager.h>
#include "ScoreSceneCommands.h"

std::unique_ptr<StaticLetterState> Letter::m_pStaticLetterState = std::make_unique<StaticLetterState>();
std::unique_ptr<FlyckeringLetterState> Letter::m_pFlyckeringLetterState = std::make_unique<FlyckeringLetterState>();
std::unique_ptr<ShouldStartFlyckering> Letter::m_pShouldStartFlyckering = std::make_unique<ShouldStartFlyckering>();
std::unique_ptr<ShouldStopFlyckering> Letter::m_pShouldStopFlyckering = std::make_unique<ShouldStopFlyckering>();

Letter::Letter(GameEngine::GameObject* gameObject) :
	GameEngine::BaseComponent(gameObject)
{

}

std::unique_ptr<GameEngine::GameObject> Letter::AddLetter(const glm::vec3& position)
{
	std::unique_ptr<GameEngine::GameObject> gameObject = std::make_unique<GameEngine::GameObject>();

	gameObject->AddComponent<GameEngine::TransformComponent>(position);
	gameObject->AddComponent<GameEngine::TextureComponent>("Alphabet.tga");
	gameObject->AddComponent<GameEngine::AnimationComponent>();
	gameObject->AddComponent<GameEngine::RenderComponent>();
	gameObject->AddComponent<Letter>();

	auto textureSizeX = gameObject->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / 16;
	auto textureSizeY = gameObject->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y / 4;

	gameObject->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });

	gameObject->GetComponent<GameEngine::AnimationComponent>()->SetHorizontalOffset(1);
	gameObject->GetComponent<GameEngine::AnimationComponent>()->SetVerticalOffset(0);

	return gameObject;
}

void Letter::AddAnimation()
{
	GetGameObject()->AddComponent<GameEngine::FSM>(m_pStaticLetterState.get(), GetGameObject()->GetComponent<GameEngine::AnimationComponent>());
	GetGameObject()->GetComponent<GameEngine::FSM>()->AddTransition(m_pStaticLetterState.get(), m_pFlyckeringLetterState.get(), m_pShouldStartFlyckering.get());
	GetGameObject()->GetComponent<GameEngine::FSM>()->AddTransition(m_pFlyckeringLetterState.get(), m_pStaticLetterState.get(), m_pShouldStopFlyckering.get());
	GetGameObject()->GetComponent<GameEngine::AnimationComponent>()->SetShouldFlyckering(true);
}

void Letter::AddNewInput()
{
	auto& input = GameEngine::InputManager::GetInstance();

	input.RemoveCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_RIGHT, GameEngine::InputState::Released }); 

	input.RemoveCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_RSHIFT, GameEngine::InputState::Pressed });

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_RIGHT, GameEngine::InputState::Released },
		std::make_unique<ChangeLetterCommand>(GetGameObject()));

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_RSHIFT, GameEngine::InputState::Pressed },
		std::make_unique<SumbitNameCommand>(GetGameObject()));
}

void Letter::DeleteInput()
{
	auto& input = GameEngine::InputManager::GetInstance(); 

	input.CleanUp(); 
}
