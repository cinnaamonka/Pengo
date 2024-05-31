#pragma once
#include <GameObjectCommand.h>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <functional>

class GameEngine::GameObject;

class PushBlockCommand :public GameEngine::GameObjectCommand
{
public:

public:
	explicit PushBlockCommand(GameEngine::GameObject* gameObject);
	~PushBlockCommand() = default;

	PushBlockCommand(const PushBlockCommand& other) = default;
	PushBlockCommand& operator=(const PushBlockCommand& other) = default;
	PushBlockCommand(PushBlockCommand&& other) noexcept = default;
	PushBlockCommand& operator=(PushBlockCommand&& other) noexcept = default;


	void Execute() override;
};
class StopPushCommand :public GameEngine::GameObjectCommand 
{
public:

public:
	explicit StopPushCommand(GameEngine::GameObject* gameObject);
	~StopPushCommand() = default;

	StopPushCommand(const StopPushCommand& other) = default;
	StopPushCommand& operator=(const StopPushCommand& other) = default;
	StopPushCommand(StopPushCommand&& other) noexcept = default;
	StopPushCommand& operator=(StopPushCommand&& other) noexcept = default;


	void Execute() override;
};
class SkipLevelCommand : public GameEngine::GameObjectCommand
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
class MuteSoundCommand : public GameEngine::GameObjectCommand
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