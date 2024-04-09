#pragma once
#include <memory>
#include <GameObject.h>

#include <glm/vec2.hpp>
#include <glm/glm.hpp>

#include <Scene.h>

class BaseBlock
{
public:
	BaseBlock(const glm::vec3& position, GameEngine::Scene* scene); 
	~BaseBlock() = default;

	BaseBlock(const BaseBlock& other) = delete;
	BaseBlock& operator=(const BaseBlock& other) = delete;
	BaseBlock(BaseBlock&& other) noexcept = delete;
	BaseBlock& operator=(BaseBlock&& other) noexcept = delete;
private:

	std::unique_ptr<GameEngine::GameObject> m_pGameObject;
};

