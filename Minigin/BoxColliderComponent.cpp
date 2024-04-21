#include "BoxColliderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "TextureComponent.h"

GameEngine::BoxCollider::BoxCollider(GameObject* pGameObject, int left, int bottom, int width, int height) :
	m_RectCollider({ left,bottom,width - 2,height -2}), BaseComponent(pGameObject)
{

}

GameEngine::BoxCollider::BoxCollider(GameObject* pGameObject, Rect shape) :
	BaseComponent(pGameObject), m_RectCollider(shape)
{

}

bool GameEngine::BoxCollider::IsCollidingHorizontally(const Rect& rectShape, HitInfo& hitInfo) const
{
	const glm::vec2 ray1(rectShape.left + 1.f, rectShape.bottom + rectShape.height / 2);
	const glm::vec2 ray2(rectShape.left + rectShape.width - 1.f, rectShape.bottom + rectShape.height / 2);

	const std::vector<glm::vec3> RectPoints = CreatePointsFromRect(m_RectCollider);

	return Raycast(RectPoints, ray1, ray2, hitInfo);;
}

bool GameEngine::BoxCollider::IsCollidingVertically(const Rect& rectShape, HitInfo& hitInfo) const
{
	const float borderDist = 5.f;

	const glm::vec2 ray1{ rectShape.left + borderDist, rectShape.bottom };
	const glm::vec2 ray2{ rectShape.left + borderDist, rectShape.bottom + rectShape.height };
	const glm::vec2 ray3{ rectShape.left + rectShape.width - borderDist, rectShape.bottom };
	const glm::vec2 ray4{ rectShape.left + rectShape.width - borderDist, rectShape.bottom + rectShape.height };

	const std::vector<glm::vec3> RectPoints = CreatePointsFromRect(m_RectCollider);

	
	return Raycast(RectPoints, ray1, ray2, hitInfo) || Raycast(RectPoints, ray3, ray4, hitInfo);
}

std::vector<glm::vec3> GameEngine::BoxCollider::CreatePointsFromRect(const Rect& rectShape) const
{
	std::vector<glm::vec3> points;

	points.push_back(glm::vec3(rectShape.left, rectShape.bottom, 0.0f)); // Bottom-left corner
	points.push_back(glm::vec3(rectShape.left + rectShape.width, rectShape.bottom, 0.0f)); // Bottom-right corner
	points.push_back(glm::vec3(rectShape.left + rectShape.width, rectShape.bottom + rectShape.height, 0.0f)); // Top-right corner
	points.push_back(glm::vec3(rectShape.left, rectShape.bottom + rectShape.height, 0.0f)); // Top-left corner

	return points;
}

