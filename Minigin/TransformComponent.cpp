#include "TransformComponent.h"

GameEngine::TransformComponent::TransformComponent(GameObject* GOptr) : Component(GOptr), m_Position(0.0f, 0.0f, 0.0f)
{}

GameEngine::TransformComponent::TransformComponent(GameObject * GOptr, glm::vec3 pos) : Component(GOptr), m_Position(pos)
{}

void GameEngine::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
