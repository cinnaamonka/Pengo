#include "pch.h"
#include "GameObject.h"
#include "TransformComponent.h"

GameEngine::GameObject::GameObject() :m_IsDestroyed(false), m_pParent(nullptr), m_pChildren{}
{

}


GameEngine::GameObject::~GameObject()
{
	delete m_pParent;
	m_pParent = nullptr;

	m_pChildren.clear();
}

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

void GameEngine::GameObject::SetParent(GameObject* newParent)
{
	if (IsValidParent(newParent))
	{
		// 1. Remove itself from the previous parent
		if (m_pParent)
		{
			m_pParent = nullptr;
		}

		// 2. Set the given parent on itself
		m_pParent = newParent;

		// 3. Add itself as a child to the given parent
		if (newParent)
		{
			newParent->SetParent(this);
		}

		// 4. Update position, rotation, and scale
		UpdateTransform();
	}
}
bool GameEngine::GameObject::IsValidParent(GameObject* newParent)
{
	// Check if the new parent is valid (not itself or one of its children)
	return newParent != this && !IsDescendant(newParent);
}
bool GameEngine::GameObject::IsDescendant(GameObject* potential_parent)
{
	// Check if the given object is a descendant of this object
	if (m_pParent == potential_parent)
	{
		return true;
	}
	else if (m_pParent == nullptr) 
	{
		return false;
	}
	else 
	{
		return m_pParent->IsDescendant(potential_parent);
	}
}
void GameEngine::GameObject::Update()
{
	for (const auto& component : m_Components)
	{
		if (auto* updatableComponent = dynamic_cast<BaseComponent*>(component.get()))
		{
			updatableComponent->Update();
		}
	}
}

void GameEngine::GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		if (auto* renderableComponent = dynamic_cast<BaseComponent*>(component.get()))
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

