#pragma once
#include <vector>
#include <memory>
#include <string>

#include <GameObject.h>

#include "BaseBlock.h"

#include <glm/vec2.hpp>
#include <glm/glm.hpp>

#include <Scene.h>

class Environment final
{
public:
	Environment(const std::string& filename, GameEngine::Scene* scene);
	~Environment() = default;

	Environment(const Environment& other) = delete;
	Environment& operator=(const Environment& other) = delete;
	Environment(Environment&& other) noexcept = delete;
	Environment& operator=(Environment&& other) noexcept = delete;

	//bool HandleCollision(Rect& shape, glm::vec2& velocity);
	//bool IsColliding(const std::vector<glm::vec3>& ver, Rect& actorShape, HitInfo& hitInfo) const; 
	//void ResetHorizontalPosition(glm::vec2& actorVelocity, Rect& actorShape, HitInfo& hitInfo) const; 
private:
	std::vector<std::vector<glm::vec3>> m_Vertices;
	std::vector<std::unique_ptr<BaseBlock>> m_pBlocks;
};

