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

	void CheckCollision(Rect& shape, glm::vec2& velocity);

	void SetCollisionCanBeChecked(bool canBeChecked)
	{
		m_CanCollisionBeChecked = canBeChecked;
	}
private:
	void ResetHorizontalPosition(glm::vec2& actorVelocity, Rect& actorShape, HitInfo& hitInfo) const;
private:
	std::vector<std::vector<glm::vec3>> m_Vertices;
	std::vector<std::unique_ptr<BaseBlock>> m_pBlocks;

	bool m_CanCollisionBeChecked;
};

