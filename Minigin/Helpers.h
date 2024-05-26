#ifndef HELPERS_H
#define HELPERS_H

#include "json.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <glm/vec2.hpp>
#include <glm/glm.hpp>

#include "BaseComponent.h"


namespace GameEngine
{
	class BlackboardComponent;
	class AnimationComponent;

	using sound_id = unsigned short;

	enum class GameModes
	{
		SinglePlayer,
		Co_op,
		Versus
	};

	struct Block
	{
		std::vector<glm::vec3> block;
		std::string tag;
	};
	struct LevelInfo
	{
		std::vector<GameEngine::Block> levelBlocks;
		std::vector<glm::vec3> enemiesPositions;
		int lifesAmount;
		int score;
		std::unordered_map<std::string, glm::vec3> hudPositions;
		GameModes gameMode;
	};

	void GetLevelInfo(std::string fileName, LevelInfo& levelInfo);
	std::vector<GameEngine::Block> GetBlocksWithTag(const std::vector<GameEngine::Block>& blocks, const std::string& tag);
	
	struct HitInfo
	{
		float lambda;
		glm::vec2 intersectPoint;
		glm::vec2 normal;
	};

	struct EnemyInfo
	{
		int index;
		glm::vec3 position;
	};
	struct Rect
	{
		int left;
		int bottom;
		int width;
		int height;
	};
	
	enum class State
	{
		PlayerDied,
		Victory
	};

	struct Sound
	{
		Sound() = default;
		Sound(const sound_id id,const float volume):
			id(id),
			volume(volume)
		{}
		sound_id id;
		float volume;
	};

	bool IsOverlapping(const Rect& r1, const Rect& r2);


	bool IsPointOnLineSegment(const glm::vec2& p, const glm::vec2& a, const glm::vec2& b);


	bool IntersectLineSegments(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& q1, const glm::vec2& q2, float& outLambda1,
		float& outLambda2, float epsilon = 1e-6);



	bool Raycast(const glm::vec3* vertices, const size_t nrVertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo);

	bool Raycast(const std::vector<glm::vec3>& vertices, const glm::vec2& rayP1, const glm::vec2& rayP2, HitInfo& hitInfo);

	void AnimationUpdate(GameEngine::AnimationComponent* animationComponent);

	bool AreVectorsCollinear(const glm::vec3& v1, const glm::vec3& v2, float tolerance = 0.0f);
	bool AreOnSameLine(const glm::vec3& referencePoint, const glm::vec3& pos1, const glm::vec3& pos2);
	bool AreNear(const glm::vec3& pos1, const glm::vec3& pos2, float threshold);
	bool AreThreePointsOnSameLine(const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3);
	bool IsPointInsideRect(const glm::vec3& point, const Rect& rect, float threshold);
	void UpdateLevelFile(const std::string& tag,const std::string& newInfo,const std::string& filename); 

	template <typename T>
	T GetFieldFromFile(const std::string& tag, const std::string& fileName)
	{
		std::filesystem::path currentPath = std::filesystem::current_path();
		std::filesystem::path parentPath = currentPath.parent_path();

		std::filesystem::path dataPath = parentPath / "Data";

		std::filesystem::path levelPath = dataPath / fileName;

		std::ifstream inputFile(levelPath);

		nlohmann::json jsonData;

		if (inputFile.is_open())
		{
			inputFile >> jsonData;
			inputFile.close();
		}
		else
		{
			throw std::runtime_error("Could not open the file for reading");
		}

		if (jsonData.contains(tag))
		{
			return jsonData[tag].get<T>();
		}
		else
		{
			throw std::runtime_error("The '" + tag + "' tag does not exist in the JSON file");
		}
	}
}

#endif // HELPERS_H