#include <Engine.h>

#include <ResourceManager.h>
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "RotationComponent.h"
#include "ImGuiComponent.h"
#include "InputCommands.h"
#include "BaseCommand.h"
#include "ActorComponent.h"
#include "ScoreObserver.h"
#include "HealthObserver.h"
#include "FPS.h"
#include "iostream"
#include "Scene.h" 
#include "SceneManager.h" 
#include "GameObject.h" 

#include "json.hpp" 


void load()
{
	auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("Demo");

	auto rotatingCharacterPengo = std::make_unique<GameEngine::GameObject>(); 
	rotatingCharacterPengo->AddComponent<GameEngine::TransformComponent>(glm::vec3(300, 350, 0)); 
	rotatingCharacterPengo->AddComponent<GameEngine::TextureComponent>("Pengo.tga"); 
	rotatingCharacterPengo->AddComponent<GameEngine::RenderComponent>(); 
	GameEngine::GameObject* referenceToRotatingCharacterPengo = rotatingCharacterPengo.get(); 
	scene.Add(std::move(rotatingCharacterPengo)); 

}

int main(int, char* [])
{

	GameEngine::Engine engine("../Data/");
	engine.Run(load);

	return 0;
}
