#include "LifeBar.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "AnimationComponent.h"

std::unique_ptr<GameEngine::GameObject> GameEngine::LifeBarFactory::CreateLifeIcon(const glm::vec3& position)
{
	std::unique_ptr<GameEngine::GameObject> gameObject = std::make_unique<GameEngine::GameObject>(); 

	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(static_cast<int>(position.x), static_cast<int>(position.y), 0)); 
	gameObject->AddComponent<GameEngine::TextureComponent>("Life.tga"); 
	gameObject->AddComponent<GameEngine::AnimationComponent>();
	gameObject->AddComponent<GameEngine::RenderComponent>();  

	return gameObject;
}
