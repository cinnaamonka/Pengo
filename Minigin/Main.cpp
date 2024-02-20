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
#include "TextObject.h"

#include "Scene.h"

#include <memory>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto gameObject = std::make_shared<dae::GameObject>();
	
	auto textureComponent = std::make_unique<dae::TextureComponent>();
	textureComponent->SetTexture("background.tga");

	auto& added = gameObject->AddComponent<dae::TextureComponent>("TextureComponent",textureComponent);
	
	auto renderComponent = std::make_unique<dae::RenderComponent>(added.GetTexture(), glm::vec3(0, 0, 0));
	gameObject->AddComponent<dae::RenderComponent>("RenderComponent", renderComponent);

	scene.Add(gameObject);

	/*go = std::make_shared<dae::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);*/

	/*auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(go);*/
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}