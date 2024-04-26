#pragma once
#include "GameObjectCommand.h"

#include <glm/vec2.hpp>
#include <glm/glm.hpp>

namespace GameEngine
{
    class GameObject;

    class MoveCommand final: public GameObjectCommand
    {
    public:
        explicit MoveCommand(GameObject* gameObject, glm::vec3 direction);
        ~MoveCommand() = default;

        MoveCommand(const MoveCommand& other) = default;
        MoveCommand& operator=(const MoveCommand& other) = default;
        MoveCommand(MoveCommand&& other) noexcept = default;
        MoveCommand& operator=(MoveCommand&& other) noexcept = default;

       
        void Execute() override;
    private:
        glm::vec3 m_Direction;
        float m_Speed;        
    };

    class PushCommand final : public GameObjectCommand
    {
    public:
        explicit PushCommand(GameObject* gameObject);
        ~PushCommand() = default;

       PushCommand(const PushCommand& other) = default;
       PushCommand& operator=(const PushCommand& other) = default;
       PushCommand(PushCommand&& other) noexcept = default;
       PushCommand& operator=(PushCommand&& other) noexcept = default;


        void Execute() override;
    };

	class StopCollisionCheck final : public GameObjectCommand
	{
	public:
		explicit StopCollisionCheck(GameObject* pGameObject);
		
		~StopCollisionCheck() = default;

		StopCollisionCheck(const StopCollisionCheck& other) = delete;
		StopCollisionCheck& operator=(const StopCollisionCheck& other) = delete;
		StopCollisionCheck(StopCollisionCheck&& other) noexcept = delete;
		StopCollisionCheck& operator=(StopCollisionCheck&& other) noexcept = delete;

		void Execute() override;

	};

}

