#pragma once
#include <memory>
#include <string>
#include <GameObject.h>

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

class Entity
{
public:
	Entity(const std::string& filePath, const glm::vec3& pos); 
	virtual ~Entity() = default;

	Entity(const Entity& other) = delete;
	Entity& operator=(const Entity& other) = delete;
	Entity(Entity&& other) noexcept = delete;
	Entity& operator=(Entity&& other) noexcept = delete;

	virtual std::unique_ptr<GameEngine::GameObject>& GetActorGameObject();
protected:
	std::unique_ptr<GameEngine::GameObject> m_pActor;
};

