#include "RenderComponent.h"

GameEngine::RenderComponent::RenderComponent(GameObject* GOptr) :
	Component(GOptr),
	m_Position(0, 0, 0),
	m_Texture(nullptr),
	m_TextureComponent(nullptr),
	m_TransformComponent(nullptr)
{
	if (GetGameObject()->HasComponent<TextureComponent>())
	{
		m_TextureComponent = GetGameObject()->GetComponent<TextureComponent>();
	}

	if (GetGameObject()->HasComponent<TransformComponent>())
	{
		m_TransformComponent = GetGameObject()->GetComponent<TransformComponent>();
	}
};

void GameEngine::RenderComponent::Render() const
{
	const auto& newTexture = m_TextureComponent->GetTexture();
	const auto& position = m_TransformComponent->GetPosition();

	if (newTexture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*newTexture, position.x, position.y);
	}
}
