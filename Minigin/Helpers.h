#include "json.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <glm/vec2.hpp>
#include <glm/glm.hpp>

#ifndef HELPERS_H
#define HELPERS_H

void GetVerticesFromJsonFile(std::string fileName, std::vector<std::vector<glm::vec3>>& m_Vertices); 

struct HitInfo
{
	float lambda;
	glm::vec2 intersectPoint;
	glm::vec2 normal;
};
struct Rect
{
	int left;
	int bottom;
	int width;
	int height;
};

bool IsOverlapping(const Rect& r1, const Rect& r2);


bool IsPointOnLineSegment(const glm::vec2& p, const glm::vec2& a, const glm::vec2& b);


bool IntersectLineSegments(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& q1, const glm::vec2& q2, float& outLambda1,
	float& outLambda2, float epsilon = 1e-6);



bool Raycast(const glm::vec3* vertices, const size_t nrVertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo);

bool Raycast(const std::vector<glm::vec3>& vertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo);

#endif // HELPERS_H