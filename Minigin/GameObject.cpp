#include <string>
#include "GameObject.h"


dae::GameObject::GameObject()
{

}


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float elapsedSec)
{
    /*if (!m_Components.empty())
    {
        auto it = m_Components.find("TextComponent");

        if (it != m_Components.end())
        {
            dae::TextComponent* textComponent = dynamic_cast<dae::TextComponent*>(it->second.get());

            textComponent->Update(elapsedSec);
        }
    }
    if (!m_Components.empty())
    {
        auto it = m_Components.find("FPS");

        if (it != m_Components.end())
        {
            dae::FPS* FPSComponent = dynamic_cast<dae::FPS*>(it->second.get());

            FPSComponent->Update(elapsedSec);
        }
    }*/

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

