#include "ScoreboardObserver.h"
#include <TransformComponent.h>
#include <TextComponent.h>
#include <RenderComponent.h>
#include <AnimationComponent.h>
#include <ResourceManager.h>
#include <FontManager.h>

ScoreboardObserver::ScoreboardObserver(GameEngine::GameObject* gameObject, GameEngine::Scene* scenePtr):
	BaseComponent(gameObject),
	m_pScene(scenePtr)
{
}

void ScoreboardObserver::Notify(const ScoreBoardData& message_from_subject)
{
	auto smallFont = GameEngine::FontManager::GetInstance().GetFont(GameEngine::FontTypes::Small); 

	auto gameObject = std::make_unique<GameEngine::GameObject>();

	gameObject->AddComponent<GameEngine::TextComponent>(message_from_subject.name, smallFont);
	gameObject->AddComponent<GameEngine::TransformComponent>(message_from_subject.position);
	gameObject->AddComponent<GameEngine::AnimationComponent>();
	gameObject->AddComponent<GameEngine::RenderComponent>();

	m_pScene->Add(std::move(gameObject));
}
