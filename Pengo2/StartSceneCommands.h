#pragma once
#include <GameObjectCommand.h>
#include <functional>

class ChooseSinglePlayer : public GameEngine::GameObjectCommand
{
public:
	ChooseSinglePlayer(GameEngine::GameObject* gameObject, std::function<void()> func); 
	~ChooseSinglePlayer() = default;

	ChooseSinglePlayer(const ChooseSinglePlayer& other) = default;
	ChooseSinglePlayer& operator=(const  ChooseSinglePlayer& other) = default;
	ChooseSinglePlayer(ChooseSinglePlayer&& other) noexcept = default;
	ChooseSinglePlayer& operator=(ChooseSinglePlayer&& other) noexcept = default;

	void Execute() override;

private:
	std::function<void()> m_pFunction;
};

class ChooseCoOp : public GameEngine::GameObjectCommand
{
public:
	ChooseCoOp(GameEngine::GameObject* gameObject, std::function<void()> func); 
	~ChooseCoOp() = default;

	ChooseCoOp(const ChooseCoOp& other) = default;
	ChooseCoOp& operator=(const  ChooseCoOp& other) = default;
	ChooseCoOp(ChooseCoOp&& other) noexcept = default;
	ChooseCoOp& operator=(ChooseCoOp&& other) noexcept = default;

	void Execute() override;

private:
	std::function<void()> m_pFunction; 
};