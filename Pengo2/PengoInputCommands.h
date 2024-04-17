#pragma once
#include <GameObjectCommand.h>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>

class GameEngine::GameObject;

class PushBlockCommand :public GameEngine::GameObjectCommand
{
public:

public:
	explicit PushBlockCommand(GameEngine::GameObject* gameObject, glm::vec3 direction);
	~PushBlockCommand() = default;

	PushBlockCommand(const PushBlockCommand& other) = default;
	PushBlockCommand& operator=(const PushBlockCommand& other) = default;
	PushBlockCommand(PushBlockCommand&& other) noexcept = default;
	PushBlockCommand& operator=(PushBlockCommand&& other) noexcept = default;


	void Execute() override;
};

