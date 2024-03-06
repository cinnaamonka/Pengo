#include "../pch.h"
#include "GameObject.h"
#include "TransformComponent.h"

GameEngine::GameObject::GameObject() :
	m_IsDestroyed(false),
	m_pParent(nullptr),
	m_pChildren{}, 
	m_pComponents{}
{

}

GameEngine::GameObject::~GameObject()
{
	if (m_pParent)
	{
		m_pParent = nullptr;
	}	

	m_pChildren.clear();
}

void GameEngine::GameObject::CleanUp()
{
	for (auto iterator = m_pComponents.begin(); iterator != m_pComponents.end();)
	{
		if ((*iterator)->IsDestroyed())
		{
			iterator = m_pComponents.erase(iterator);
		}
		else
		{
			iterator++;
		}
	}
}

void GameEngine::GameObject::SetParent(GameObject* newParent, bool keepWorldPosition)
{
	if (IsValidParent(newParent))
	{
		// 1. Remove itself from the previous parent
		if (m_pParent)
		{
			m_pParent = nullptr;
		}
		if (keepWorldPosition)
		{
			// 2. Update position, rotation, and scale
			GetComponent<TransformComponent>()->UpdateWorldPosition();
		}
		// 3. Set the given parent on itself
		m_pParent = newParent;

		// 4. Add itself as a child to the given parent
		if (newParent)
		{
			newParent->AddChild(this);
		}
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
void GameEngine::GameObject::DetachFromParent()
{
	m_pParent = nullptr;
}
void GameEngine::GameObject::AddChild(GameObject* newChild)
{
	m_pChildren.push_back(newChild);
}
void GameEngine::GameObject::Update()
{
	for (const auto& component : m_pComponents)
	{
		if (auto* updatableComponent = dynamic_cast<BaseComponent*>(component.get()))
		{
			updatableComponent->Update();
		}
	}
}

void GameEngine::GameObject::Render() const
{
	for (const auto& component : m_pComponents)
	{
		if (auto* renderableComponent = dynamic_cast<BaseComponent*>(component.get()))
		{
			renderableComponent->Render();
		}
	}
}



