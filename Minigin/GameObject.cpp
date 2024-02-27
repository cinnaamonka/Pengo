#include <string>
#include "GameObject.h"


GameEngine::GameObject::GameObject() :m_IsDestroyed(false)
{

}


GameEngine::GameObject::~GameObject() = default;

void GameEngine::GameObject::CleanUp()
{
	for (auto iterator = m_Components.begin(); iterator != m_Components.end();)
	{
		if ((*iterator)->IsDestroyed())
		{
			iterator = m_Components.erase(iterator);
		}
		else
		{
			iterator++;
		}
	}
}

void GameEngine::GameObject::Update()
{
	for (const auto& component : m_Components)
	{
		if (auto* updatableComponent = dynamic_cast<Component*>(component.get()))
		{
			updatableComponent->Update();
		}
	}
}

void GameEngine::GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		if (auto* renderableComponent = dynamic_cast<Component*>(component.get()))
		{
			renderableComponent->Render();
		}
	}
}

void GameEngine::GameObject::SetPosition(float x, float y)
{
	for (const auto& component : m_Components)
	{
		if (auto* transformComponent = dynamic_cast<GameEngine::TransformComponent*>(component.get()))
		{
			transformComponent->SetPosition(x, y, 0);
		}
	}
}

