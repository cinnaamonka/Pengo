#pragma once
#include <memory>
#include <GameObject.h>

#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <Helpers.h>
#include <BoxColliderComponent.h>

#include <Scene.h>

class BoxCollider;

class BaseBlock
{
public:
	BaseBlock(const glm::vec3& position, GameEngine::Scene* scene,const std::string& filename); 
	~BaseBlock() = default;

	BaseBlock(const BaseBlock& other) = delete;
	BaseBlock& operator=(const BaseBlock& other) = delete;
	BaseBlock(BaseBlock&& other) noexcept = delete;
	BaseBlock& operator=(BaseBlock&& other) noexcept = delete;

	bool IsCollidingHorizontally(const GameEngine::Rect& rectShape, GameEngine::HitInfo& hitInfo);
	bool IsCollidingVertically(const GameEngine::Rect& rectShape, GameEngine::HitInfo& hitInfo); 

private:

	std::unique_ptr<GameEngine::GameObject> m_pGameObject;
	GameEngine::BoxCollider* m_pBoxCollider;

	const int m_BlockSize;
};

