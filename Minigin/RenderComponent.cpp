#include "RenderComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "FSM.h"
#include "Renderer.h"
#include "AnimationComponent.h"

GameEngine::RenderComponent::RenderComponent(GameObject* GOptr) :
	BaseComponent(GOptr),
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
	m_pAnimationComponent = GetGameObject()->GetComponent<GameEngine::AnimationComponent>();
};

void GameEngine::RenderComponent::Render()
{
	const auto& newTexture = m_TextureComponent->GetTexture();
	const auto& position = m_TransformComponent->GetWorldPosition();
	const auto& dimensions = m_TransformComponent->GetDimensions();

	if (!m_pAnimationComponent) return;

	glm::vec3 movementDirection = m_pAnimationComponent->GetMovementDirection();

	bool IsMovingLeft = false;

	if (m_pBlackboard)
	{  
		IsMovingLeft = movementDirection.x < 0;
	}
	
	// only width can be checked
	if (newTexture != nullptr && dimensions.width == 0)
	{
		Renderer::GetInstance().RenderTexture(*newTexture, position.x, position.y);
	}
	else if (newTexture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*newTexture, position.x, position.y, { dimensions.left, dimensions.bottom,
			dimensions.width,dimensions.height }, IsMovingLeft);
	}
}
