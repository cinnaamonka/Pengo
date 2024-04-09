#include "Environment.h"
#include <Helpers.h>
#include <memory>

#include "BaseBlock.h"


Environment::Environment(const std::string& filename, GameEngine::Scene* scene)
{
	GetVerticesFromJsonFile("Level.json", m_Vertices);

	int amountOfBlocks = m_Vertices.size();

	for (int i = 0; i < amountOfBlocks; ++i)
	{
		std::unique_ptr<BaseBlock> pBaseBlock = std::make_unique<BaseBlock>(m_Vertices[i][0], scene); 

		m_pBlocks.push_back(std::move(pBaseBlock)); 
	}
}

//bool Environment::HandleCollision(Rect& shape, glm::vec2& velocity)
//{
//	HitInfo hitInfo{};
//
//	for (const std::vector< glm::vec3>& ver : m_Vertices)
//	{
//		if (IsColliding(ver, shape, hitInfo))
//		{
//			ResetHorizontalPosition(velocity, shape, hitInfo);
//
//			/*if (isCollidingGround(ver, shape, hitInfo)) 
//			{
//				ResetVerticalPosition(velocity, shape, hitInfo);
//			}*/
//
//			break;
//		}
//	}
//}
//void Environment::ResetHorizontalPosition(glm::vec2& actorVelocity, Rect& actorShape,HitInfo& hitInfo) const
//{
//
//	if (hitInfo.intersectPoint.x < actorShape.left + actorShape.width / 2)
//	{
//		actorShape.left = hitInfo.intersectPoint.x;
//	}
//	else if (hitInfo.intersectPoint.x > actorShape.left + actorShape.width / 2)
//	{
//		actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
//	}
//
//	actorVelocity.x = 0.0f;
//}
//bool Environment::IsColliding(const std::vector<glm::vec3>& ver, Rect& actorShape, HitInfo& hitInfo) const
//{
//	const glm::vec2 ray1(actorShape.left, actorShape.bottom + actorShape.height / 2);
//	const glm::vec2 ray2(actorShape.left + actorShape.width, actorShape.bottom + actorShape.height / 2);
//
//	return Raycast(ver, ray1, ray2, hitInfo); 
//}
