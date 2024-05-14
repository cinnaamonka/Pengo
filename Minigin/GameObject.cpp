#include "GameObject.h"
#include "TransformComponent.h"
#include <memory>

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
	if (!this) return;
	if (!m_IsDestroyed) return;

    for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
    {
		(*it).release();
    }
    m_pComponents.clear();
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
	if(m_pComponents.empty()) return;
	for (const auto& component : m_pComponents)
	{
		if (auto* updatableComponent = dynamic_cast<BaseComponent*>(component.get()))
		{
			if (updatableComponent != nullptr)
			{
				updatableComponent->Update();
			}
			
		}
	}
}

void GameEngine::GameObject::Render() const
{
	if (!this) return;
	for (const auto& component : m_pComponents)
	{
		if (!component->IsDestroyed())
		{
			component->Render();

		}
	}
}



