#include "HUD.h"
#include "ScoreBar.h"
#include "Scene.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "AnimationComponent.h"
#include "TextComponent.h"
#include "SnoBeeShower.h"
#include "LifeBar.h"
#include "GameObject.h"


void GameEngine::HUD::AddScoreBar(const glm::vec3& position, Scene* scene, int currentScore)
{
	m_Score = currentScore;
	auto gameObject = ScoreBarFactory::CreateScoreBar(position, currentScore);
	m_pScoreBar = gameObject.get();
	scene->Add(std::move(gameObject));
	
	std::unique_ptr<GameEngine::GameObject> additionalText = std::make_unique<GameEngine::GameObject>();

	additionalText->AddComponent<GameEngine::TransformComponent>(glm::vec3(static_cast<int>(position.x + 15), static_cast<int>(position.y + 5), 0));
	additionalText->AddComponent<GameEngine::TextureComponent>("2.tga");
	additionalText->AddComponent<GameEngine::AnimationComponent>();
	additionalText->AddComponent<GameEngine::RenderComponent>();

	scene->Add(std::move(additionalText));

	std::unique_ptr<GameEngine::GameObject> PText = std::make_unique<GameEngine::GameObject>();

	auto PPos = m_pScoreBar->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();

	PText->AddComponent<GameEngine::TransformComponent>(glm::vec3(static_cast<int>(position.x + 25), static_cast<int>(position.y + 5), 0));
	PText->AddComponent<GameEngine::TextureComponent>("P.tga");
	PText->AddComponent<GameEngine::AnimationComponent>();
	PText->AddComponent<GameEngine::RenderComponent>();

	scene->Add(std::move(PText));
}

void GameEngine::HUD::AddLifeBar(const glm::vec3& position, Scene* scene, int lifesAmount)
{
	for (int i = 0; i < lifesAmount; ++i)
	{
		auto gameObject = LifeBarFactory::CreateLifeIcon({ position.x + i * 20,position.y,position.z });
		m_pLifes.push_back(gameObject.get());
		scene->Add(std::move(gameObject));
	}

}

void GameEngine::HUD::CreateGameMode(const glm::vec3& position, Scene* scene, GameEngine::GameModes gameMode)
{
	auto gameObject = GameMode::CreateGameMode(position, gameMode);
	m_pGameMode = gameObject.get();
	scene->Add(std::move(gameObject));

	auto modePos = m_pGameMode->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition(); 

	std::unique_ptr<GameEngine::GameObject> PText = std::make_unique<GameEngine::GameObject>(); 

	PText->AddComponent<GameEngine::TransformComponent>(glm::vec3(static_cast<int>(modePos.x + 10), static_cast<int>(position.y + 5), 0));
	PText->AddComponent<GameEngine::TextureComponent>("P.tga"); 
	PText->AddComponent<GameEngine::AnimationComponent>(); 
	PText->AddComponent<GameEngine::RenderComponent>(); 

	scene->Add(std::move(PText)); 
}

void GameEngine::HUD::CreateSnoBeesBar(const glm::vec3& position,int snoBeesAmount, Scene* scene)
{
	if (scene)
	{
		m_pScene = scene;
	}

	for (int i = 0; i < snoBeesAmount; ++i)
	{
		auto gameObject = SnoBeeShower::CreateSnoBeesBar({ position.x + i * 10,position.y,position.z });
		m_pSnoBeesLifes.push_back(gameObject.get()); 
		m_pScene->Add(std::move(gameObject));
	}
}

void GameEngine::HUD::Notify(const HUDEvent& messageFromSubject)
{
	switch (messageFromSubject)
	{
	case HUDEvent::InceaseScore500:
	{
		std::string scoreStrBefore = std::to_string(m_Score);
		int digitsBefore = static_cast<int>(scoreStrBefore.length());

		m_Score += 500;

		std::string scoreStrAfter = std::to_string(m_Score);
		int digitsAfter = static_cast<int>(scoreStrAfter.length());

		if (digitsAfter != digitsBefore)
		{
			glm::vec3 currentPos = m_pScoreBar->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();

			currentPos.x -= 15.f;

			m_pScoreBar->GetComponent<GameEngine::TransformComponent>()->SetLocalPosition(currentPos);
		}

		m_pScoreBar->GetComponent<GameEngine::TextComponent>()->SetText(scoreStrAfter);
		break;
	}
	case HUDEvent::DecreaseLife:
	{
		if (!m_pLifes.empty())
		{
			auto lastElement = std::prev(m_pLifes.end());

			(*lastElement)->SetIsDestroyed(true);
			m_pLifes.pop_back();

		}
		break;
	}
	case HUDEvent::IncreaseScore30:
	{
		std::string scoreStrBefore = std::to_string(m_Score);
		int digitsBefore = static_cast<int>(scoreStrBefore.length());

		m_Score += 30;

		std::string scoreStrAfter = std::to_string(m_Score);
		int digitsAfter = static_cast<int>(scoreStrAfter.length());

		if (digitsAfter != digitsBefore)
		{
			glm::vec3 currentPos = m_pScoreBar->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();

			currentPos.x -= 5.f;

			m_pScoreBar->GetComponent<GameEngine::TransformComponent>()->SetLocalPosition(currentPos);
		}

		m_pScoreBar->GetComponent<GameEngine::TextComponent>()->SetText(scoreStrAfter);
		break;
	}
	case HUDEvent::DecreaseSnoBeesAmount:
	{
		if (!m_pSnoBeesLifes.empty())
		{
			auto lastElement = std::prev(m_pSnoBeesLifes.end());

			(*lastElement)->SetIsDestroyed(true);
			m_pSnoBeesLifes.pop_back();
		}
		break;
	}
	case HUDEvent::AddSnoBeesLife:
	{
		auto lastElement = std::prev(m_pSnoBeesLifes.end());
		auto position = (*(lastElement))->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();


		CreateSnoBeesBar({ position.x + 10,position.y,position.z }, 1);
		break;
	}
	default:
		break;
	}

}
