#pragma once
#include "json.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <glm/vec2.hpp>
#include <glm/glm.hpp>


void GetVerticesFromJsonFile(std::string fileName, std::vector<std::vector<glm::vec3>>& m_Vertices)
{
	std::filesystem::path currentPath = std::filesystem::current_path();
	std::filesystem::path parentPath = currentPath.parent_path();

	std::filesystem::path dataPath = parentPath / "Data";

	std::filesystem::path filePath = dataPath / fileName;

	std::ifstream inputFile(filePath);

	if (!inputFile.is_open())
	{
		std::cerr << "Failed to open " << fileName << std::endl;
		return;
	}

	nlohmann::json jsonDoc;

	try
	{
		inputFile >> jsonDoc;

		std::vector<std::vector<glm::vec3>> allBlocks;

		for (const auto& blockData : jsonDoc["level"])
		{
			glm::vec3 position;
			position.x = blockData["position"]["left"];
			position.y = blockData["position"]["top"];

			const int size = 20;

			std::vector<glm::vec3> block{};
			block.push_back(position);
			block.push_back({ position.x + size, position.y,0 });
			block.push_back({ position.x, position.y + size,0 });
			block.push_back({ position.x + size, position.y + size,0 });

			m_Vertices.push_back(block);
		}
	}
	catch (const nlohmann::json::parse_error& e)
	{
		std::cerr << "JSON Parsing error: " << e.what() << std::endl;
		return;
	}
}
struct HitInfo
{
	float lambda;
	glm::vec2 intersectPoint;
	glm::vec2 normal;
};
struct Rect
{
	float left;
	float bottom;
	float width;
	float height;
};
//
//bool IsOverlapping(const Rect& r1, const Rect& r2)
//{
//	// If one rectangle is on left side of the other
//	if ((r1.left + r1.width) < r2.left || (r2.left + r2.width) < r1.left)
//	{
//		return false;
//	}
//
//	// If one rectangle is under the other
//	if (r1.bottom > (r2.bottom + r2.height) || r2.bottom > (r1.bottom + r1.height))
//	{
//		return false;
//	}
//
//	return true;
//}
////
//bool IsPointOnLineSegment(const glm::vec2& p, const glm::vec2& a, const glm::vec2& b)
//{
//	glm::vec3 ap{ a, p,0 }, bp{ b, p,0 };
//	// If not on same line, return false
//	if (glm::length(glm::cross(ap, bp)) > 0.001f)
//	{
//		return false;
//	}
//
//	// Both vectors must point in opposite directions if p is between a and b
//	if (glm::dot(ap, bp) > 0)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//bool IntersectLineSegments(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& q1, const glm::vec2& q2, float& outLambda1,
//	float& outLambda2, float epsilon = 1e-6)
//{
//	bool intersecting{ false };
//
//	// Calculate vectors from points
//	glm::vec3 p1p2{ p2.x - p1.x, p2.y - p1.y, 0 };
//	glm::vec3 q1q2{ q2.x - q1.x, q2.y - q1.y, 0 };
//
//	// Cross product to determine if parallel
//	glm::vec3 denom = glm::cross(p1p2, q1q2); 
//
//	// Don't divide by zero
//	if (glm::length(denom) > epsilon)
//	{
//		intersecting = true;
//
//		glm::vec3 p1q1{ p1.x - q1.x, p1.y - q1.y, 0 }; // Vector from q1 to p1  
//
//		float num1 = glm::cross(p1q1, q1q2).z; 
//		float num2 = glm::cross(p1q1, p1p2).z; 
//		outLambda1 = num1 / glm::length(denom); 
//		outLambda2 = num2 / glm::length(denom); 
//	}
//	else // are parallel
//	{
//		// Connect start points
//		glm::vec3 p1q1{ p1, q1,0 };
//
//		// Cross product to determine if segments and the line connecting their start points are parallel, 
//		// if so, than they are on a line
//		// if not, then there is no intersection
//		if (glm::length(glm::cross(p1q1,q1q2)) > epsilon)
//		{
//			return false;
//		}
//
//		// Check the 4 conditions
//		outLambda1 = 0;
//		outLambda2 = 0;
//		if (IsPointOnLineSegment(p1, q1, q2) ||
//			IsPointOnLineSegment(p2, q1, q2) ||
//			IsPointOnLineSegment(q1, p1, p2) ||
//			IsPointOnLineSegment(q2, p1, p2))
//		{
//			intersecting = true;
//		}
//	}
//	return intersecting;
//}
//
//
//bool Raycast(const glm::vec3* vertices, const size_t nrVertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo)
//{
//	if (nrVertices == 0)
//	{
//		return false;
//	}
//
//	std::vector<HitInfo> hits;
//
//	Rect r1{}, r2{};
//	// r1: minimal AABB rect enclosing the ray
//	r1.left = std::min(rayP1.x, rayP2.x);
//	r1.bottom = std::min(rayP1.y, rayP2.y);
//	r1.width = std::max(rayP1.x, rayP2.x) - r1.left;
//	r1.height = std::max(rayP1.y, rayP2.y) - r1.bottom;
//
//	// Line-line intersections.
//	for (size_t idx{ 0 }; idx <= nrVertices; ++idx)
//	{
//		// Consider line segment between 2 consecutive vertices
//		// (modulo to allow closed polygon, last - first vertice)
//		glm::vec2 q1 = vertices[(idx + 0) % nrVertices];
//		glm::vec2 q2 = vertices[(idx + 1) % nrVertices];
//
//		// r2: minimal AABB rect enclosing the 2 vertices
//		r2.left = std::min(q1.x, q2.x);
//		r2.bottom = std::min(q1.y, q2.y);
//		r2.width = std::max(q1.x, q2.x) - r2.left;
//		r2.height = std::max(q1.y, q2.y) - r2.bottom;
//
//		if (IsOverlapping(r1, r2))
//		{
//			float lambda1{};
//			float lambda2{};
//			if (IntersectLineSegments(rayP1, rayP2, q1, q2, lambda1, lambda2))
//			{
//				if (lambda1 > 0 && lambda1 <= 1 && lambda2 > 0 && lambda2 <= 1)
//				{
//					HitInfo linesHitInfo{};
//					linesHitInfo.lambda = lambda1;
//					linesHitInfo.intersectPoint = glm::vec2{ rayP1.x + ((rayP2.x - rayP1.x) * lambda1), rayP1.y + ((rayP2.y - rayP1.y) * lambda1) };
//					glm::vec2 q1q2 = q2 - q1;
//					glm::vec2 normal = glm::vec2(-q1q2.y, q1q2.x);  
//					linesHitInfo.normal = glm::normalize(normal);
//					hits.push_back(linesHitInfo);
//				}
//			}
//		}
//	}
//
//	if (hits.size() == 0)
//	{
//		return false;
//	}
//
//	// Get closest intersection point and copy it into the hitInfo parameter
//	hitInfo = *std::min_element
//	(
//		hits.begin(), hits.end(),
//		[](const HitInfo& first, const HitInfo& last)
//		{
//			return first.lambda < last.lambda;
//		}
//	);
//	return true;
//}
//bool Raycast(const std::vector<glm::vec3>& vertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo)
//{
//	return Raycast(vertices.data(), vertices.size(), rayP1, rayP2, hitInfo);
//}
