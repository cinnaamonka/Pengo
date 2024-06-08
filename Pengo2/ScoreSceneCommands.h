#pragma once
#include <GameObjectCommand.h>
#include <glm/glm.hpp>
#include <vector>
#include <Subject.h>
#include "Structs.h"

class GameEngine::GameObject;

class ChangeLetterCommand final: public GameEngine::GameObjectCommand
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

class SumbitNameCommand final: public GameEngine::GameObjectCommand
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
class SwitchToNextLetter final: public GameEngine::GameObjectCommand
{
public:
	SwitchToNextLetter(std::vector<GameEngine::GameObject*>& letters,int& currentLetterIndex,int score,const glm::vec3& position,
		GameEngine::Subject<ScoreBoardData>* subject);
	~SwitchToNextLetter() = default;

	SwitchToNextLetter(const SwitchToNextLetter& other) = default;
	SwitchToNextLetter& operator=(const SwitchToNextLetter& other) = default;
	SwitchToNextLetter(SwitchToNextLetter&& other) noexcept = default;
	SwitchToNextLetter& operator=(SwitchToNextLetter&& other) noexcept = default;

	void Execute() override;
private:
	int m_CurrentLetterIndex = 0;
	std::vector<GameEngine::GameObject*> m_pLetters;
	int m_Score;
	GameEngine::Subject<ScoreBoardData>* m_Subject;
	glm::vec3 m_Position;
};
