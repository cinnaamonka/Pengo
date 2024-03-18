#pragma once
#include "BaseCommand.h"

namespace GameEngine
{
	class GameObject;

	class GameObjectCommand : public BaseCommand
	{
	public:
		explicit GameObjectCommand(GameObject* pGameObject) :m_pGameObject{ pGameObject } {}
		virtual ~GameObjectCommand() = default;

		GameObjectCommand(const GameObjectCommand& other) = delete;
		GameObjectCommand& operator=(const GameObjectCommand& other) = delete;
		GameObjectCommand(GameObjectCommand&& other) noexcept = delete;
		GameObjectCommand& operator=(GameObjectCommand&& other) noexcept = delete;

		virtual void Execute() override = 0;

	private:
		GameObject* m_pGameObject;

	protected:
		GameObject* GetGameObject() const { return m_pGameObject; }
	};

}

