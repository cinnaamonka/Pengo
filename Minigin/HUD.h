#pragma once
#include "BaseComponent.h"

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include "IObserver.h"
#include "Helpers.h"
#include "GameMode.h"

namespace GameEngine
{
	class Scene;
	class GameObject;

	enum class HUDEvent
	{
		InceaseScore500,
		IncreaseScore30,
		DecreaseLife
	};

	class HUD final : public IObserver<HUDEvent>
	{
	public:
		HUD() = default;
		~HUD() = default;

		HUD(const HUD& other) = delete;
		HUD& operator=(const HUD& other) = delete;
		HUD(HUD&& other) noexcept = delete;
		HUD& operator=(HUD&& other) noexcept = delete;

		void AddScoreBar(const glm::vec3& position,Scene* scene);
		void AddLifeBar(const glm::vec3& position, Scene* scene,int lifesAmount);
		void CreateGameMode(const glm::vec3& position, Scene* scene, GameEngine::GameModes gameMode);
		void Notify(const HUDEvent& messageFromSubject) override;
	private:
		GameEngine::GameObject* m_pScoreBar;
		std::vector<GameEngine::GameObject*> m_pLifes;
		GameEngine::GameObject* m_pGameMode;

		int m_Score = 0;
	};

}

