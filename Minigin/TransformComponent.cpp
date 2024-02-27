#include "pch.h"
#include "TransformComponent.h"

GameEngine::TransformComponent::TransformComponent(GameObject* GOptr) :
	BaseComponent(GOptr),
	m_LocalPosition(0.0f, 0.0f, 0.0f),
	m_WorldPosition(0.0f, 0.0f, 0.0f),
	m_IsWorldPositionUpdated(false)
{}

GameEngine::TransformComponent::TransformComponent(GameObject* GOptr, glm::vec3 pos) :
	BaseComponent(GOptr),
	m_LocalPosition(pos),
	m_WorldPosition(pos),
	m_IsWorldPositionUpdated(false)
{}

void GameEngine::TransformComponent::SetLocalPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
}

void GameEngine::TransformComponent::SetLocalPosition(const glm::vec3& position)
{
	m_LocalPosition = position;
}

void GameEngine::TransformComponent::SetWorldPosition(float x, float y, float z)
{
	m_WorldPosition.x = x;
	m_WorldPosition.y = y;
	m_WorldPosition.z = z;
}

void GameEngine::TransformComponent::SetWorldPosition(const glm::vec3& position)
{
	m_WorldPosition = position;
}

void GameEngine::TransformComponent::Translate(float x, float y, float z)
{
	Translate(glm::vec3{ x,y,z });
}

void GameEngine::TransformComponent::Translate(const glm::vec3& translation)
{
	SetLocalPosition(translation);
}

void GameEngine::TransformComponent::UpdateWorldPosition()
{
	if (GetGameObject()->GetParent() == nullptr)
	{
		m_WorldPosition = m_LocalPosition;
	}
	else
	{
		m_WorldPosition = m_LocalPosition + GetGameObject()->GetParent()->GetComponent<TransformComponent>()->GetWorldPosition();
	}

	m_IsWorldPositionUpdated = true;
}

void GameEngine::TransformComponent::SetIsWorldPositionUpdated()
{
	m_IsWorldPositionUpdated = false;

	GameObject* gameObject = GetGameObject();

	if (gameObject) 
	{
		for (const auto& pChild : gameObject->GetChildren()) 
		{
			TransformComponent* transformComponent = pChild->GetComponent<TransformComponent>();

			if (transformComponent != nullptr && transformComponent->IsWorldPositionUpdated()) 
			{
				pChild->GetComponent<TransformComponent>()->SetIsWorldPositionUpdated();
			}
		}
	}
}

glm::vec3 GameEngine::TransformComponent::GetWorldPosition()
{
	if (!m_IsWorldPositionUpdated)
	{
		UpdateWorldPosition();
	}
	return m_WorldPosition;
}


