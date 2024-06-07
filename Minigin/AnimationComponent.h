#pragma once
#include "BaseComponent.h"
#include "Helpers.h"

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "TransformComponent.h"


namespace GameEngine
{
	class AnimationComponent final : public GameEngine::BaseComponent
	{

	public:
		AnimationComponent(GameEngine::GameObject* pGameObject);
		AnimationComponent(const AnimationComponent& other) = delete;
		AnimationComponent(AnimationComponent&& other) = delete;
		AnimationComponent& operator=(const AnimationComponent& other) = delete;
		AnimationComponent& operator=(AnimationComponent&& other) = delete;
		~AnimationComponent() = default;


		void Update() override;
		void ChangeTexture();

		int GetNumberOfFrames() const { return m_NumberOfFrames; }
		void SetNumberOfFrames(int numberOfFrames) { m_NumberOfFrames = numberOfFrames; }

		float GetAnimationTime() const { return m_AnimationTime; }
		void SetAnimationTime(float animationTime) { m_AnimationTime = animationTime; }

		int GetFramesPerSec() const { return m_FramesPerSec; }
		void SetFramesPerSec(int framesPerSec) { m_FramesPerSec = framesPerSec; }

		int GetAnimationFrame()const { return m_AnimationFrame; }
		void SetAnimationFrame(int animationFrame) { m_AnimationFrame = animationFrame; }

		int GetHorizontalOffset() const { return m_HorizontalOffset; }
		void SetHorizontalOffset(int horizontalOffset) { m_HorizontalOffset = horizontalOffset; }

		int GetVerticalOffset() const { return m_VerticalOffset; }
		void SetVerticalOffset(int verticalOffset) { m_VerticalOffset = verticalOffset; }

		glm::vec3 GetMovementDirection() const { return m_MovementDirection; }
		void SetMovementDirection(glm::vec3 movementDirection) { m_MovementDirection = movementDirection; };

		float GetTimeOffset() const { return m_TimeOffset; }
		void SetTimeOffset(float timeOffset) { m_TimeOffset = timeOffset; }

		bool GetIsDestroyed() const { return m_IsDestroyed; }
		void SetIsDestroyed(bool isDestroyed) { m_IsDestroyed = isDestroyed; }

		int GetAnimationTimes() const { return m_AnimationTimes; }
		void SetAnimationTimes(int animationTimes) { m_AnimationTimes = animationTimes; }

		bool GetWasInputGiven() const { return m_WasInputGiven; }
		void SetWasInputGiven(bool wasInputGiven) { m_WasInputGiven = wasInputGiven; }

		bool GetWasPushed() const { return m_WasPushed; }
		void SetWasPushed(bool wasPushed) { m_WasPushed = wasPushed; }

		glm::vec3 GetPos() const { return m_Pos; }
		void SetPos(glm::vec3 pos) { m_Pos = pos; }

		float GetSpeed() const { return m_Speed; }
		void SetSpeed(float speed) { m_Speed = speed; }

		bool GetIsChasing() const { return m_IsChasing; }
		void SetIsChasing(bool isChasing) { m_IsChasing = isChasing; }

		bool GetIsVertical() const { return m_IsVertical; }
		void SetIsVertical(bool isVertical) { m_IsVertical = isVertical; }

		bool GetIsHorizontal() const { return m_IsHorizontal; }
		void SetIsHorizontal(bool isHorizontal) { m_IsHorizontal = isHorizontal; }

		bool GetShouldFlyckering() const { return m_ShouldFlyckering; }
		void SetShouldFlyckering(bool shouldFlyckering) { m_ShouldFlyckering = shouldFlyckering; }

		void Destroy(); 

	private:
		int m_NumberOfFrames;
		float m_AnimationTime;
		int m_FramesPerSec = 10;
		int m_AnimationFrame;
		int m_HorizontalOffset;
		int m_VerticalOffset;
		glm::vec3 m_MovementDirection;
		bool m_IsDestroyed;
		float m_TimeOffset;
		int m_AnimationTimes = 0;
		bool m_WasInputGiven;
		bool m_WasPushed;
		glm::vec3 m_Pos;
		float m_Speed;
		bool m_IsChasing;
		bool m_IsVertical;
		bool m_IsHorizontal;
		bool m_ShouldFlyckering;

		GameEngine::TransformComponent* m_pTransformComponent;
	};
}

