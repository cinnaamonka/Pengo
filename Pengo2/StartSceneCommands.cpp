#include "StartSceneCommands.h"
#include <Helpers.h>

ChooseSinglePlayer::ChooseSinglePlayer(GameEngine::GameObject* gameObject, std::function<void()> func):
	GameEngine::GameObjectCommand(gameObject),
	m_pFunction(func)
{
}

void ChooseSinglePlayer::Execute()
{
	GameEngine::UpdateLevelFile("game_mode", GameEngine::GameModes::SinglePlayer, "Level0.json");
	GameEngine::UpdateLevelFile("game_mode", GameEngine::GameModes::SinglePlayer, "Level1.json");
	GameEngine::UpdateLevelFile("game_mode", GameEngine::GameModes::SinglePlayer, "Level2.json");

	m_pFunction();
}
ChooseCoOp::ChooseCoOp(GameEngine::GameObject* gameObject, std::function<void()> func):
	GameEngine::GameObjectCommand(gameObject),
	m_pFunction(func)
{
}

void ChooseCoOp::Execute()
{
	GameEngine::UpdateLevelFile("game_mode", GameEngine::GameModes::Co_op, "Level0.json"); 
	GameEngine::UpdateLevelFile("game_mode", GameEngine::GameModes::Co_op, "Level1.json"); 
	GameEngine::UpdateLevelFile("game_mode", GameEngine::GameModes::Co_op, "Level2.json"); 

	m_pFunction();
}

ChooseVersus::ChooseVersus(GameEngine::GameObject* gameObject, std::function<void()> func):
	GameEngine::GameObjectCommand(gameObject),
	m_pFunction(func)
{

}

void ChooseVersus::Execute()
{
	GameEngine::UpdateLevelFile("game_mode", GameEngine::GameModes::Versus, "Level0.json");
	GameEngine::UpdateLevelFile("game_mode", GameEngine::GameModes::Versus, "Level1.json");
	GameEngine::UpdateLevelFile("game_mode", GameEngine::GameModes::Versus, "Level2.json");

	m_pFunction();
}
