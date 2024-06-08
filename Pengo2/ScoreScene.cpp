#include "ScoreScene.h"
#include <SceneManager.h>
#include <TransformComponent.h>
#include <TextComponent.h>
#include <RenderComponent.h>
#include <AnimationComponent.h>
#include <TextureComponent.h>
#include <Texture2D.h>
#include <TimeManager.h>
#include <InputManager.h>
#include "ScoreSceneCommands.h"
#include "ScoreboardObserver.h"
#include <SoundServiceLocator.h>
#include <SoundSystem.h>
#include <algorithm>
#include <iterator> 
#include <ResourceManager.h>


void ScoreScene::Initialize(int score)
{
	m_Score = score;

	GameEngine::TimeManager::StopAllTimers();
	GameEngine::SoundServiceLocator::GetInstance().GetSoundSystemInstance().Pause();

	auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("ScoreScene");

	m_pFinalPlayerScore = std::make_unique<GameEngine::GameObject>();
	m_pFinalPlayerScore->AddComponent<GameEngine::TransformComponent>(glm::vec3{ 0,0,0 });
	m_pFinalPlayerScore->AddComponent<ScoreboardObserver>(&scene);

	auto scoreBoardObserver = m_pFinalPlayerScore->GetComponent<ScoreboardObserver>();
    m_AddScoreToScoreboardEvent.Attach(scoreBoardObserver); 

	auto bigFont = GameEngine::ResourceManager::GetInstance().GetFont(GameEngine::FontTypes::Big);
	auto middleFont = GameEngine::ResourceManager::GetInstance().GetFont(GameEngine::FontTypes::Middle);
	auto smallFont = GameEngine::ResourceManager::GetInstance().GetFont(GameEngine::FontTypes::Small);

	AddText(m_ScoreLablePosition, "SCORE", &scene, middleFont);
	AddText(m_InitialsLabelPosition, "ENTER YOUR INITIALS", &scene, bigFont);
	AddText(m_NameLabelPosition, "NAME", &scene, middleFont);
	AddText(m_CurrentScorePosition, std::to_string(score), &scene, middleFont); 
	AddText(m_ArrowsInstructionPosition, "Right arrow on keyboard/A on controller to change letters", &scene, smallFont);
	AddText(m_SumbitInstructionPosition, "Press Shift/X to enter letter and submit", &scene, smallFont);

	const int incremenet = 30;

	for (int i = 0; i < m_LettersAmount; ++i) 
	{
		auto letter = Letter::AddLetter(glm::vec3{ m_LettersPosition.x + i * incremenet,m_LettersPosition.y,0 }); 
		letter->GetComponent<Letter>()->DeleteInput();
		m_pLetters.push_back(letter.get());
		scene.Add(std::move(letter));
	}

	ShowLeaderBord(&scene, smallFont, m_LeaderBordPositionPosition); 
	InitializeInputSystem(m_pFinalPlayerScore.get(),GameEngine::GameModes::SinglePlayer);

	m_pLetters[0]->GetComponent<Letter>()->AddNewInput();
	m_pLetters[0]->GetComponent<Letter>()->AddAnimation();

	AddText(m_SubNameLabelPosition, "SCORE", &scene, middleFont);
	AddText(m_SubScoreLabelPosition, "NAME", &scene, middleFont);

	AddLeadersList(&scene, smallFont);
   
}

std::unique_ptr<GameEngine::GameObject> ScoreScene::AddLetter(const glm::vec3& position)
{
	std::unique_ptr<GameEngine::GameObject> pFirstLetter = std::make_unique<GameEngine::GameObject>();
	pFirstLetter->AddComponent<GameEngine::TransformComponent>(position);
	pFirstLetter->AddComponent<GameEngine::TextureComponent>("Alphabet.tga");
	pFirstLetter->AddComponent<GameEngine::AnimationComponent>();
	pFirstLetter->AddComponent<GameEngine::RenderComponent>();

	auto textureSizeX = pFirstLetter->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().x / m_LettersInTextureRow;
	auto textureSizeY = pFirstLetter->GetComponent<GameEngine::TextureComponent>()->GetTexture()->GetSize().y / m_LettersInTextureColumn;

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

	if (scoresMap.find(m_Score) != scoresMap.end())
	{
		scoresMap.erase(m_Score); 
	}

	scoresMap.insert({ m_Score, "" });
	std::map<int, std::string, std::greater<int>> sortedMap(scoresMap.begin(), scoresMap.end());

	if (sortedMap.size() > m_LeadersAmount)
	{
		auto it = sortedMap.begin(); 
		std::advance(it, m_LeadersAmount);
		sortedMap.erase(it, sortedMap.end()); 
	}
	const int incrementY = 40;

	const int incrementX = 250;

	int i = 0;
	for (auto it = sortedMap.begin(); it != sortedMap.end(); ++it, ++i)
	{
		if (it->first == m_Score)
		{
			m_pFinalPlayerScore->GetComponent<GameEngine::TransformComponent>()->SetLocalPosition(glm::vec3{ pos.x + incrementX, pos.y + i * incrementY, 0 });
		}
		std::unique_ptr<GameEngine::GameObject> name = std::make_unique<GameEngine::GameObject>();
		name->AddComponent<GameEngine::TransformComponent>(glm::vec3{ pos.x, pos.y + i * 40, 0 }); 
		name->AddComponent<GameEngine::TextComponent>(std::to_string(it->first), font); 
		name->AddComponent<GameEngine::AnimationComponent>(); 
		name->AddComponent<GameEngine::RenderComponent>(); 
		scene->Add(std::move(name));

		std::unique_ptr<GameEngine::GameObject> score = std::make_unique<GameEngine::GameObject>();
		score->AddComponent<GameEngine::TransformComponent>(glm::vec3{ pos.x + incrementX, pos.y + i * incrementY, 0 });
		score->AddComponent<GameEngine::TextComponent>(it->second, font);
		score->AddComponent<GameEngine::AnimationComponent>();
		score->AddComponent<GameEngine::RenderComponent>();
		scene->Add(std::move(score));
	}
}
void ScoreScene::AddLeadersList(GameEngine::Scene* scene, std::shared_ptr<GameEngine::Font> font)
{
	const int increment = 40;
	float yPos = m_LeadersPosition.y;

	for (int i = 1; i <= m_LeadersAmount; ++i)
	{
		std::string suffix;
		switch (i) {
		case 1: suffix = "st"; break;
		case 2: suffix = "nd"; break;
		case 3: suffix = "rd"; break;
		default: suffix = "th"; break;
		}

		std::string text = std::to_string(i) + suffix; 

		AddText(glm::vec3{ m_LeadersPosition.x, yPos, 0 }, text, scene, font);

		yPos += increment;
	}
}
void ScoreScene::InitializeInputSystem(GameEngine::GameObject*, GameEngine::GameModes,int deviceIndex)
{
	auto& input = GameEngine::InputManager::GetInstance();

	auto m_Controller = std::make_unique<GameEngine::Controller>(deviceIndex);
	auto m_Keyboard = std::make_unique<GameEngine::Keyboard>();
	input.AddDevice(std::move(m_Controller));
	input.AddDevice(std::move(m_Keyboard));

	auto position = m_pFinalPlayerScore->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();

	input.AddCommand<GameEngine::Keyboard>(
		GameEngine::InputKeyboardBinding{ SDL_SCANCODE_RSHIFT, GameEngine::InputState::Released },
		std::make_unique<SwitchToNextLetter>(m_pLetters, m_CurrentLetterIndex,m_Score, position ,&m_AddScoreToScoreboardEvent));

	input.AddCommand<GameEngine::Controller>(
		GameEngine::InputControllerBinding{ GameEngine::DeviceButton::XINPUT_CONTROLLER_X, GameEngine::InputState::Released,0 },
		std::make_unique<SwitchToNextLetter>(m_pLetters, m_CurrentLetterIndex, m_Score, position, &m_AddScoreToScoreboardEvent));

}