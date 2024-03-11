#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"

void GameEngine::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void GameEngine::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

void GameEngine::SceneManager::Cleanup()
{
	for (const auto& scene : m_Scenes)
	{
		scene->CleanUp();
	}
}

GameEngine::Scene& GameEngine::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}
