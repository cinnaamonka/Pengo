#include <string>
#include "GameObject.h"


dae::GameObject::GameObject()
{

}


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float elapsedSec)
{

    for (const auto& component : m_Components) 
    {
        if (auto* updatableComponent = dynamic_cast<Component*>(component.get())) 
        {
            updatableComponent->Update(elapsedSec);
        }
    }
}

void dae::GameObject::Render() const
{
    for (const auto& component : m_Components) 
    { 
        if (auto* renderableComponent = dynamic_cast<Component*>(component.get())) 
        { 
            renderableComponent->Render(); 
        } 
    } 
} 

void dae::GameObject::SetPosition(float x, float y)
{
    for (const auto& component : m_Components) 
    {
        if (auto* transformComponent = dynamic_cast<dae::TransformComponent*>(component.get()))
        {
            transformComponent->SetPosition(x, y, 0);
        }
    }
}

