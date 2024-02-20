#include <string>
#include "GameObject.h"


dae::GameObject::GameObject()
{

}


dae::GameObject::~GameObject() = default;

//void dae::GameObject::Update(float elapsedSec){}

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
	m_TransformComponent->SetPosition(x, y, 0.0f);
}

