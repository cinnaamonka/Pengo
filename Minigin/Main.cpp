#include "pch.h"

#include "Engine.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "BaseComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPS.h"

#include "Scene.h"

void load()
{
	auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("Demo");

	// Game object background

	auto gameObject = std::make_unique<GameEngine::GameObject>();
	
	// transform component to background
	gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(0, 0, 0));

	// texture component to background
	gameObject->AddComponent<GameEngine::TextureComponent>("background.tga");

	// render component to background
	gameObject->AddComponent<GameEngine::RenderComponent>();

	scene.Add(std::move(gameObject));

	//// game object DAELabel

	//gameObject = std::make_unique<GameEngine::GameObject>();

	//// transform component to DAELabel
	//gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(216, 180, 0));

	//// add texture component to DAELabel
	//gameObject->AddComponent<GameEngine::TextureComponent>("logo.tga");

	//// add render component to DAELAbel
	//gameObject->AddComponent<GameEngine::RenderComponent>();

	//scene.Add(std::move(gameObject));

	//// add text object 
	//auto font = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	//gameObject = std::make_unique<GameEngine::GameObject>();

	//// add transform component to this game object
	//gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(170, 20, 0));
	//
	//// add text component 
 //   gameObject->AddComponent<GameEngine::TextComponent>("Programming 4 Assignment", font);

	//// add render component
	//gameObject->AddComponent<GameEngine::RenderComponent>();

	//scene.Add(std::move(gameObject));

	//// add fps game object
	//gameObject = std::make_unique<GameEngine::GameObject>();

	//// add fps component
	//gameObject->AddComponent<GameEngine::FPS>();

	////add transform component
	//gameObject->AddComponent<GameEngine::TransformComponent>(glm::vec3(20, 20, 0));
	//
	//// add text component 
	//gameObject->AddComponent<GameEngine::TextComponent>("FPS", font);

	//// add render component
	//gameObject->AddComponent<GameEngine::RenderComponent>();

	//scene.Add(std::move(gameObject));
}

int main(int, char*[]) {
	GameEngine::Engine engine("../Data/");
	engine.Run(load);
    return 0;
}