#include "ScoreScene.h"
#include <SceneManager.h>
#include <TransformComponent.h>
#include <TextComponent.h>
#include <ResourceManager.h>
#include <RenderComponent.h>
#include <AnimationComponent.h>
#include <TextureComponent.h>
#include <Texture2D.h>
#include <TimeManager.h>
#include <InputManager.h>
#include "ScoreSceneCommands.h"
#include <memory>

void ScoreScene::Initialize(int score)
{
    GameEngine::TimeManager::StopAllTimers();

    auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("ScoreScene");

    std::unique_ptr<GameEngine::GameObject> pEnterYourInitials = std::make_unique<GameEngine::GameObject>();
   

    auto bigFont = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);
    auto middleFont = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);

    AddText(glm::vec3{ 150,150,0 }, "SCORE", &scene, bigFont);
    AddText(glm::vec3{ 170,100,0 }, "ENTER YOUR INITIALS", &scene, bigFont);
    AddText(glm::vec3{ 400,150,0 }, "NAME", &scene, middleFont);
    AddText(glm::vec3{ 160,200,0 }, std::to_string(score), &scene, middleFont);

    for (int i = 0; i < 3; ++i)
    {
        auto letter = Letter::AddLetter(glm::vec3{ 400 + i * 30,200,0 });
        m_pLetters.push_back(letter.get());
        scene.Add(std::move(letter));
    }
    InitializeInputSystem(pEnterYourInitials.get());

    m_pLetters[0]->GetComponent<Letter>()->AddNewInput();
    m_pLetters[0]->GetComponent<Letter>()->AddAnimation();

  
}

std::unique_ptr<GameEngine::GameObject> ScoreScene::AddLetter(const glm::vec3& position)
{
    std::unique_ptr<GameEngine::GameObject> pFirstLetter = std::make_unique<GameEngine::GameObject>();
    pFirstLetter->AddComponent<GameEngine::TransformComponent>(position);
    pFirstLetter->AddComponent<GameEngine::TextureComponent>("Alphabet.tga");
    pFirstLetter->AddComponent<GameEngine::AnimationComponent>();
    pFirstLetter->AddComponent<GameEngine::RenderComponent>();

    auto textureSizeX = pFirstLetter->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / 16;
    auto textureSizeY = pFirstLetter->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y / 4;

    pFirstLetter->GetComponent<GameEngine::TransformComponent>()->SetDimensions({ 0, 0,textureSizeX,textureSizeY });

    pFirstLetter->GetComponent<GameEngine::AnimationComponent>()->SetHorizontalOffset(1);
    pFirstLetter->GetComponent<GameEngine::AnimationComponent>()->SetVerticalOffset(0);

    return pFirstLetter;
}

void ScoreScene::AddText(const glm::vec3& position, const std::string& text, GameEngine::Scene* scene, std::shared_ptr<GameEngine::Font> font)
{
    std::unique_ptr<GameEngine::GameObject> pFinalScoreText = std::make_unique<GameEngine::GameObject>();
    pFinalScoreText->AddComponent<GameEngine::TransformComponent>(position);
    pFinalScoreText->AddComponent<GameEngine::TextComponent>(text, font);
    pFinalScoreText->AddComponent<GameEngine::AnimationComponent>();
    pFinalScoreText->AddComponent<GameEngine::RenderComponent>();
    scene->Add(std::move(pFinalScoreText));
}
void ScoreScene::InitializeInputSystem(GameEngine::GameObject*)
{
    auto& input = GameEngine::InputManager::GetInstance();

    auto m_Controller = std::make_unique<GameEngine::Controller>(0);
    auto m_Keyboard = std::make_unique<GameEngine::Keyboard>();
    input.AddDevice(std::move(m_Controller));
    input.AddDevice(std::move(m_Keyboard));

    input.AddCommand<GameEngine::Keyboard>(
        GameEngine::InputKeyboardBinding{ SDL_SCANCODE_RSHIFT, GameEngine::InputState::Released },
        std::make_unique<SwitchToNextLetter>(m_pLetters, m_CurrentLetterIndex)); 

}