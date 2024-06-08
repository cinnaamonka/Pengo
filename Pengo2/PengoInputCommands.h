#pragma once
#include <GameObjectCommand.h>
#include <glm/glm.hpp>
#include <functional>

class GameEngine::GameObject;

class PushBlockCommand final:public GameEngine::GameObjectCommand
{
public:
	explicit PushBlockCommand(GameEngine::GameObject* gameObject, GameEngine::GameObject* actor);
	~PushBlockCommand() = default;

	PushBlockCommand(const PushBlockCommand& other) = default;
	PushBlockCommand& operator=(const PushBlockCommand& other) = default;
	PushBlockCommand(PushBlockCommand&& other) noexcept = default;
	PushBlockCommand& operator=(PushBlockCommand&& other) noexcept = default;


	void Execute() override;
private:
	GameEngine::GameObject* m_pActor;
};
class BreakBlockCommand final:public GameEngine::GameObjectCommand
{
public:
	explicit BreakBlockCommand(GameEngine::GameObject* gameObject);
	~BreakBlockCommand() = default;

	BreakBlockCommand(const BreakBlockCommand& other) = default;
	BreakBlockCommand& operator=(const BreakBlockCommand& other) = default;
	BreakBlockCommand(BreakBlockCommand&& other) noexcept = default;
	BreakBlockCommand& operator=(BreakBlockCommand&& other) noexcept = default;


	void Execute() override;
};
class StopPushCommand final:public GameEngine::GameObjectCommand 
{

public:
	explicit StopPushCommand(GameEngine::GameObject* gameObject);
	~StopPushCommand() = default;

	StopPushCommand(const StopPushCommand& other) = default;
	StopPushCommand& operator=(const StopPushCommand& other) = default;
	StopPushCommand(StopPushCommand&& other) noexcept = default;
	StopPushCommand& operator=(StopPushCommand&& other) noexcept = default;


	void Execute() override;
};
class SkipLevelCommand final: public GameEngine::GameObjectCommand
{
public:
	SkipLevelCommand(GameEngine::GameObject* gameObject, std::function<void()> func);
	~SkipLevelCommand() = default;

	SkipLevelCommand(const SkipLevelCommand& other) = default;
	SkipLevelCommand& operator=(const  SkipLevelCommand& other) = default;
	SkipLevelCommand(SkipLevelCommand&& other) noexcept = default;
	SkipLevelCommand& operator=(SkipLevelCommand&& other) noexcept = default;

	void Execute() override;

private:
	std::function<void()> m_pFunction;
};
class MuteSoundCommand final: public GameEngine::GameObjectCommand
{
public:
	MuteSoundCommand(GameEngine::GameObject* gameObject);
	~MuteSoundCommand() = default;

	MuteSoundCommand(const MuteSoundCommand& other) = default;
	MuteSoundCommand& operator=(const  MuteSoundCommand& other) = default;
	MuteSoundCommand(MuteSoundCommand&& other) noexcept = default;
	MuteSoundCommand& operator=(MuteSoundCommand&& other) noexcept = default;

	void Execute() override;
private:
	bool m_IsMuted;
};