#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace GameEngine;

unsigned int Scene::m_idCounter = 0;

void GameEngine::Scene::CleanUp()
{
	// remove components from game objects
	for (const std::unique_ptr<GameObject>& gameObject : m_pObjects)
	{
		gameObject->CleanUp();
	}
	
	// destroy objects 
	for (auto it = m_pObjects.begin(); it != m_pObjects.end();)
	{
		if ((*it)->IsDestroyed())
		{
			it = m_pObjects.erase(it);
		}
			
		else
		{
			it++;
		}
	}
}

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject>&& object)
{
	m_pObjects.emplace_back(std::move(object));
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
}

void Scene::Update()
{
	for(auto& object : m_pObjects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

