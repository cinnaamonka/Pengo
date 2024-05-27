#pragma once
#include <GameObjectCommand.h>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>

class GameEngine::GameObject;

class ChangeLetterCommand : public GameEngine::GameObjectCommand
{
public:
	ChangeLetterCommand(GameEngine::GameObject* gameObject);
	~ChangeLetterCommand() = default;

	ChangeLetterCommand(const ChangeLetterCommand& other) = default;
	ChangeLetterCommand& operator=(const ChangeLetterCommand& other) = default;
	ChangeLetterCommand(ChangeLetterCommand&& other) noexcept = default;
	ChangeLetterCommand& operator=(ChangeLetterCommand&& other) noexcept = default;

	void Execute() override;
private:
	char m_CurrentLetter = 'A';
};

class SumbitNameCommand : public GameEngine::GameObjectCommand
{
public:
	SumbitNameCommand(GameEngine::GameObject* gameObject);
	~SumbitNameCommand() = default;

	SumbitNameCommand(const SumbitNameCommand& other) = default;
	SumbitNameCommand& operator=(const SumbitNameCommand& other) = default;
	SumbitNameCommand(SumbitNameCommand&& other) noexcept = default;
	SumbitNameCommand& operator=(SumbitNameCommand&& other) noexcept = default;

	void Execute() override;
};

