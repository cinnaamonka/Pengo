#include "TransformComponent.h"

#include "iostream"

GameEngine::TransformComponent::TransformComponent(GameObject* GOptr) :
	BaseComponent(GOptr),
	m_LocalPosition(0.0f, 0.0f, 0.0f),
	m_WorldPosition(0.0f, 0.0f, 0.0f),
	m_IsPositionDirty(true)
{}

GameEngine::TransformComponent::TransformComponent(GameObject* GOptr, glm::vec3 pos) :
	BaseComponent(GOptr),
	m_LocalPosition(pos),
	m_WorldPosition(pos),
	m_IsPositionDirty(true)
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
	
	SetPositionDirty();
}

void GameEngine::TransformComponent::SetWorldPosition(float x, float y, float z)
{
	SetWorldPosition({ x,y,z });
}

void GameEngine::TransformComponent::SetWorldPosition(const glm::vec3& position)
{
	if (GetGameObject()->GetParent() == nullptr)
	{
		SetLocalPosition(position);
	}
	else
	{
		SetLocalPosition(GetGameObject()->GetParent()->GetComponent<TransformComponent>()->GetWorldPosition());
	}
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
		const auto pos = GetGameObject()->GetParent()->GetComponent<TransformComponent>()->GetWorldPosition();
		m_WorldPosition = m_LocalPosition + pos;
	}

	m_IsPositionDirty = false;
}

void GameEngine::TransformComponent::SetPositionDirty()
{
	m_IsPositionDirty = true;

	GameObject* gameObject = GetGameObject();

	if (gameObject) 
	{
		for (auto pChild : gameObject->GetChildren()) 
		{
			TransformComponent* transformComponent = pChild->GetComponent<TransformComponent>();

			if (transformComponent != nullptr && transformComponent->IsPositionDirty())
			{
				pChild->GetComponent<TransformComponent>()->SetPositionDirty();
			}
		}
	}
}

glm::vec3 GameEngine::TransformComponent::GetWorldPosition()
{
	if (m_IsPositionDirty)
	{
		UpdateWorldPosition();
	}
	return m_WorldPosition;
}



