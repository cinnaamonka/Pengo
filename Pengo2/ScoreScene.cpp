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
#include <algorithm>
#include <iterator> 


void ScoreScene::Initialize(int score)
{
	m_Score = score;

	GameEngine::TimeManager::StopAllTimers();

	auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("ScoreScene");

	std::unique_ptr<GameEngine::GameObject> pEnterYourInitials = std::make_unique<GameEngine::GameObject>();

	auto bigFont = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 28);
	auto middleFont = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	auto smallFont = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	AddText(glm::vec3{ 150,150,0 }, "SCORE", &scene, middleFont);
	AddText(glm::vec3{ 170,100,0 }, "ENTER YOUR INITIALS", &scene, bigFont);
	AddText(glm::vec3{ 400,150,0 }, "NAME", &scene, middleFont);
	AddText(glm::vec3{ 160,180,0 }, std::to_string(score), &scene, middleFont);

	for (int i = 0; i < 3; ++i)
	{
		auto letter = Letter::AddLetter(glm::vec3{ 400 + i * 30,180,0 });
		letter->GetComponent<Letter>()->DeleteInput();
		m_pLetters.push_back(letter.get());
		scene.Add(std::move(letter));
	}

	InitializeInputSystem(pEnterYourInitials.get());

	m_pLetters[0]->GetComponent<Letter>()->AddNewInput();
	m_pLetters[0]->GetComponent<Letter>()->AddAnimation();

	AddText(glm::vec3{ 150,230,0 }, "SCORE", &scene, middleFont);
	AddText(glm::vec3{ 400,230,0 }, "NAME", &scene, middleFont);
	AddText(glm::vec3{ 100,270,0 }, "1st", &scene, smallFont);
	AddText(glm::vec3{ 100,310,0 }, "2nd", &scene, smallFont);
	AddText(glm::vec3{ 100,350,0 }, "3rd", &scene, smallFont);
	AddText(glm::vec3{ 100,390,0 }, "4th", &scene, smallFont);
	AddText(glm::vec3{ 100,430,0 }, "5th", &scene, smallFont);

	ShowLeaderBord(&scene,smallFont,glm::vec3{160,270,0}); 
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
void ScoreScene::ShowLeaderBord(GameEngine::Scene* scene, std::shared_ptr<GameEngine::Font> font,const glm::vec3& pos)
{
	std::map<int,std::string> scoresMap = GameEngine::ReadScoresFromJson("Score.json");

	std::map<int, std::string, std::greater<int>> sortedMap(scoresMap.begin(), scoresMap.end());

	if (sortedMap.size() > 5)
	{
		auto it = sortedMap.begin(); 
		std::advance(it, 5); 
		sortedMap.erase(it, sortedMap.end()); 
	}

	int i = 0;
	for (auto it = sortedMap.begin(); it != sortedMap.end(); ++it, ++i)
	{
		std::unique_ptr<GameEngine::GameObject> name = std::make_unique<GameEngine::GameObject>();
		name->AddComponent<GameEngine::TransformComponent>(glm::vec3{ pos.x, pos.y + i * 40, 0 }); 
		name->AddComponent<GameEngine::TextComponent>(it->second, font); 
		name->AddComponent<GameEngine::AnimationComponent>(); 
		name->AddComponent<GameEngine::RenderComponent>(); 
		scene->Add(std::move(name));

		std::unique_ptr<GameEngine::GameObject> score = std::make_unique<GameEngine::GameObject>();
		score->AddComponent<GameEngine::TransformComponent>(glm::vec3{ pos.x + 250, pos.y + i * 40, 0 });
		score->AddComponent<GameEngine::TextComponent>(std::to_string(it->first), font);
		score->AddComponent<GameEngine::AnimationComponent>();
		score->AddComponent<GameEngine::RenderComponent>();
		scene->Add(std::move(score));
	}
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
		std::make_unique<SwitchToNextLetter>(m_pLetters, m_CurrentLetterIndex,m_Score));

}