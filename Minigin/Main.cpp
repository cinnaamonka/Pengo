#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Components.h"

#include "Scene.h"

#include <memory>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// Game object background

	auto gameObject = std::make_shared<dae::GameObject>();
	
	// transform component to background
	gameObject->AddComponent<dae::TransformComponent>(glm::vec3(0, 0, 0));

	// texture component to background
	gameObject->AddComponent<dae::TextureComponent>("background.tga");

	// render component to background
	gameObject->AddComponent<dae::RenderComponent>();

	scene.Add(gameObject);

	// game object DAELabel

	gameObject = std::make_shared<dae::GameObject>();

	// transform component to DAELabel
	gameObject->AddComponent<dae::TransformComponent>(glm::vec3(216, 180, 0));

	// add texture component to DAELabel
	gameObject->AddComponent<dae::TextureComponent>("logo.tga");

	// add render component to DAELAbel
	gameObject->AddComponent<dae::RenderComponent>();  

	scene.Add(gameObject);  

	// add text object 
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	gameObject = std::make_shared<dae::GameObject>();

	// add transform component to this game object
	gameObject->AddComponent<dae::TransformComponent>(glm::vec3(170, 20, 0));
	
	// add text component 
    gameObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);

	// add render component
	gameObject->AddComponent<dae::RenderComponent>();

	scene.Add(gameObject);

	// add fps game object

	// make unique
	gameObject = std::make_shared<dae::GameObject>();

	// add fps component
	gameObject->AddComponent<dae::FPS>();

	//add transform component
	gameObject->AddComponent<dae::TransformComponent>(glm::vec3(20, 20, 0));
	
	// add text component 
	gameObject->AddComponent<dae::TextComponent>("FPS", font);

	// add render component
	gameObject->AddComponent<dae::RenderComponent>();

	scene.Add(gameObject);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}