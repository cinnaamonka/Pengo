#include "HUD.h"
#include "ScoreBar.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "AnimationComponent.h"
#include "TextComponent.h"
#include <memory>
#include "Texture2D.h"

void GameEngine::HUD::AddScoreBar(const glm::vec3& position, Scene* scene)
{
	auto gameObject = ScoreBarFactory::CreateScoreBar(position);
	m_pScoreBar = gameObject.get(); 
	scene->Add(std::move(gameObject));

	std::unique_ptr<GameEngine::GameObject> additionalText = std::make_unique<GameEngine::GameObject>(); 

	auto scorePos = m_pScoreBar->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();
	additionalText->AddComponent<GameEngine::TransformComponent>(glm::vec3(static_cast<int>(scorePos.x + 50), static_cast<int>(position.y + 5), 0));
	additionalText->AddComponent<GameEngine::TextureComponent>("2.tga");
	additionalText->AddComponent<GameEngine::AnimationComponent>();
	additionalText->AddComponent<GameEngine::RenderComponent>();

	scene->Add(std::move(additionalText));

	std::unique_ptr<GameEngine::GameObject> PText = std::make_unique<GameEngine::GameObject>();

	auto PPos = m_pScoreBar->GetComponent<GameEngine::TransformComponent>()->GetLocalPosition();
	PText->AddComponent<GameEngine::TransformComponent>(glm::vec3(static_cast<int>(PPos.x + 60), static_cast<int>(position.y + 5), 0));
	PText->AddComponent<GameEngine::TextureComponent>("P.tga");
	PText->AddComponent<GameEngine::AnimationComponent>();
	PText->AddComponent<GameEngine::RenderComponent>();

	scene->Add(std::move(PText));
}
