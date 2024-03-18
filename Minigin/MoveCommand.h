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
        explicit MoveCommand(GameObject* gameObject, glm::vec3 direction, float speed);
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

}

