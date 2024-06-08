#pragma once
#include "GameObjectCommand.h"
#include "TransformComponent.h"
#include "ActorComponent.h"
#include "AnimationComponent.h"

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
        GameEngine::TransformComponent* m_pTransformComponent;
        GameEngine::ActorComponent* m_pActorComponent;
        GameEngine::AnimationComponent* m_pAnimationComponent;
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
    private:
        GameEngine::ActorComponent* m_pActorComponent;
        GameEngine::AnimationComponent* m_pAnimationComponent;
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
    private:

        GameEngine::ActorComponent* m_pActorComponent;
	};


}

