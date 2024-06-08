#include <Engine.h>
#include "Game.h"
#include "LevelLoader.h"
#include <SoundSystem.h>
#include <SoundServiceLocator.h>
#include <SoundLogSystem.h>

int main(int, char* [])
{

	GameEngine::Engine engine("./Data/");
	LevelLoader levelLoader(3);


	GameEngine::SoundServiceLocator::RegisterSoundSystem(std::make_unique<GameEngine::SoundLogSystem>
		(std::make_unique<GameEngine::SoundSystem>()));

	auto& soundSystem = GameEngine::SoundServiceLocator::GetSoundSystemInstance(); 

	for (const auto& [soundType, filePath] : SOUND_PATH_MAPPING) 
	{
		soundSystem.Load(filePath, static_cast<GameEngine::sound_id>(static_cast<int>(soundType))); 
	}

	bool startGame = true;
	bool continueGame = false;

	if (startGame)
	{
		startGame = engine.Run(levelLoader.GetStartScreen());  
		continueGame = true;
	}
	
	while (continueGame && levelLoader.HasNextLevel() && startGame)
	{
		continueGame = engine.Run(levelLoader.GetNextLevelLoader());
	}
	if (!levelLoader.HasNextLevel())
	{
		continueGame = engine.Run(levelLoader.GetFinalScene());
	}
	
	return 0;
}
