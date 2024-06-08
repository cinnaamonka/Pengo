#pragma once
#include "BaseComponent.h"

#include <glm/glm.hpp>

#include <memory>
#include <vector>
#include "IObserver.h"
#include "GameMode.h"

namespace GameEngine
{
	class Scene;
	class GameObject;

	enum class HUDEvent
	{
		InceaseScore500,
		IncreaseScore30,
		DecreaseLife,
		DecreaseSnoBeesAmount,
		AddSnoBeesLife
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

		void AddScoreBar(const glm::vec3& position,Scene* scene,int currentScore);
		void AddLifeBar(const glm::vec3& position, Scene* scene,int lifesAmount);
		void CreateGameMode(const glm::vec3& position, Scene* scene, GameEngine::GameModes gameMode);
		void CreateSnoBeesBar(const glm::vec3& position, int snoBeesAmount, Scene* scene = nullptr);
		void Notify(const HUDEvent& messageFromSubject) override;

		int GetScore() const { return m_Score; }
		void SetScore(int score) { m_Score = score; }
	private:
		GameEngine::GameObject* m_pScoreBar;
		std::vector<GameEngine::GameObject*> m_pLifes;
		std::vector<GameEngine::GameObject*> m_pSnoBeesLifes;
		GameEngine::GameObject* m_pGameMode;

		int m_Score = 0;

		Scene* m_pScene;
	};

}

