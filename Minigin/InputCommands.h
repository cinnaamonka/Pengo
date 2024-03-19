#pragma once
#include "GameObjectCommand.h"
//#include "ScoreComponent.h"

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

	class ScoreCommand final : public GameObjectCommand
	{
	public:
		explicit ScoreCommand(GameObject* pGameObject, int amount);
		
		~ScoreCommand() = default;

		ScoreCommand(const ScoreCommand& other) = delete;
		ScoreCommand& operator=(const ScoreCommand& other) = delete;
		ScoreCommand(ScoreCommand&& other) noexcept = delete;
		ScoreCommand& operator=(ScoreCommand&& other) noexcept = delete;

		void Execute() override;
	
	private:
		int m_Amount;

	};

}

