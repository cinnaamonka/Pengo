#pragma once
#include <BaseGame.h>
#include <memory>
#include "Letter.h"
#include <Scene.h>
#include <Font.h>
#include <Subject.h>
#include "Structs.h"

class StartScreen : public GameEngine::BaseGame
{
public:
	StartScreen() = default;
	~StartScreen() = default;
	StartScreen(const StartScreen& other) = delete;
	StartScreen(StartScreen&& other) = delete;
	StartScreen& operator=(const StartScreen& other) = delete;
	StartScreen& operator=(StartScreen&& other) = delete;

	bool IsLevelComplete() override 
	{
		return m_IsLevelComplete; 
	};

	void ResetLevel() override {};
	void CompleteLevel()
	{
		m_IsLevelComplete = true;
	}
	void Initialize();
private:
	void InitializeInputSystem(GameEngine::GameObject*, GameEngine::GameModes gameMode,int deviceIndex = 0) override;
	void AddPicture(const std::string& texturePath, const glm::vec3& position,GameEngine::Scene* scene);
	void AddText(const std::string& text, const glm::vec3& position, GameEngine::Scene* scene,std::shared_ptr<GameEngine::Font> font);
private:
	bool m_IsLevelComplete;
	const glm::vec3& m_LabelPosition = glm::vec3{ 140,50,0 };
	const glm::vec3& m_SinglePlayerPosition = glm::vec3{ 280,300,0 };
	const glm::vec3& m_Co_OpPosition = glm::vec3{ 300,370,0 };
	const glm::vec3& m_VSPosition = glm::vec3{ 300,440,0 };
	const glm::vec3& m_AButton = glm::vec3{ 380,290,0 };
	const glm::vec3& m_BButton = glm::vec3{ 350,360,0 };
	const glm::vec3& m_XButton = glm::vec3{ 360,430,0 };
	const glm::vec3& m_MuteButtonPosition = glm::vec3{ 20,20,0 };

	std::unique_ptr<GameEngine::GameObject> m_pInputGameObject;
};

