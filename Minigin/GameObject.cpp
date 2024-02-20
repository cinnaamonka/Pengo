#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::GameObject(dae::Texture2D texture)
{
	m_Components.emplace_back(std::make_unique<TextureComponent>(texture));
	m_TransformComponent = this->AddComponent<Transform>();
	m_TextureComponent = this->AddComponent<TextureComponent>(texture);
}


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float elapsedSec){}

void dae::GameObject::Render() const
{
	const auto& pos = m_TransformComponent.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_TextureComponent.GetTexture(), pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_TextureComponent.GetTexture() = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_TransformComponent.SetPosition(x, y, 0.0f);
}

