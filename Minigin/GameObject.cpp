#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject()
{
	m_TransformComponent = std::make_unique<TransformComponent>(this->AddComponent<TransformComponent>());
	m_TextureComponent = std::make_unique<TextureComponent>(this->AddComponent<TextureComponent>());
	m_RenderComponent = std::make_unique<RenderComponent>(this->AddComponent<RenderComponent>(m_TextureComponent, m_TransformComponent));
}


dae::GameObject::~GameObject() = default;

//void dae::GameObject::Update(float elapsedSec){}

void dae::GameObject::Render() const
{
	m_RenderComponent->Render();
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	const auto& myTexture = ResourceManager::GetInstance().LoadTexture(filename);
	m_TextureComponent->SetTexture(myTexture);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_TransformComponent->SetPosition(x, y, 0.0f);
}

