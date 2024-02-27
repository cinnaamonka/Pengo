#include <string>
#include "GameObject.h"


GameEngine::GameObject::GameObject()
{

}


GameEngine::GameObject::~GameObject() = default;

void GameEngine::GameObject::Update(float elapsedSec)
{

    for (const auto& component : m_Components) 
    {
        if (auto* updatableComponent = dynamic_cast<Component*>(component.get())) 
        {
            updatableComponent->Update(elapsedSec);
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

