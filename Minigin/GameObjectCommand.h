#pragma once
#include "BaseCommand.h"

class GameObject;

class GameActorCommand : public BaseCommand
{
public:
	explicit GameActorCommand(GameObject* pGameObject) :m_pGameObject{ pGameObject } {}
	virtual ~GameActorCommand() = default;

	GameActorCommand(const GameActorCommand& other) = delete;
	GameActorCommand& operator=(const GameActorCommand& other) = delete;
	GameActorCommand(GameActorCommand&& other) noexcept = delete;
	GameActorCommand& operator=(GameActorCommand&& other) noexcept = delete;

	virtual void Execute() override = 0;

private:
	GameObject* m_pGameObject;

protected:
	GameObject* GetGameObject() const { return m_pGameObject; }
};

