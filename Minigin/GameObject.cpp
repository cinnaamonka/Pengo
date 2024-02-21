#include <string>
#include "GameObject.h"


dae::GameObject::GameObject()
{

}


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
    if (!m_Components.empty())
    {
        auto it = m_Components.find("TextComponent");

        if (it != m_Components.end())
        {
            dae::TextComponent* textComponent = dynamic_cast<dae::TextComponent*>(it->second.get());

            textComponent->Update();
        }
    }
}

void dae::GameObject::Render() const
{
    if (!m_Components.empty())
    {
        auto it = m_Components.find("RenderComponent");

        if (it != m_Components.end())
        {
            dae::RenderComponent* renderComponent = dynamic_cast<dae::RenderComponent*>(it->second.get());

            renderComponent->Render();

        }
    }
}

void dae::GameObject::SetPosition(float x, float y)
{
    if (!m_Components.empty())
    {
        auto it = m_Components.find("TransformComponent");

        if (it != m_Components.end())
        {
            dae::TransformComponent* renderComponent = dynamic_cast<dae::TransformComponent*>(it->second.get());

            renderComponent->SetPosition(x,y,0);
        }
    }
}

