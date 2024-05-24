#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"

void GameEngine::SceneManager::Update()
{
	m_pCurrentScene->Update();
}

void GameEngine::SceneManager::Render()
{
	m_pCurrentScene->Render();
}

void GameEngine::SceneManager::Cleanup()
{
	m_pCurrentScene->CleanUp();
}

void GameEngine::SceneManager::Destroy()
{
	m_pCurrentScene->Destroy();
}

void GameEngine::SceneManager::DeleteCurrentScene()
{
	m_pCurrentScene.reset();
}

GameEngine::Scene& GameEngine::SceneManager::CreateScene(const std::string& name)
{
	m_pCurrentScene = std::unique_ptr<Scene>(new Scene(name));
	return *m_pCurrentScene;
}
