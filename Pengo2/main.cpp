#include <Engine.h>
#include "Game.h"
#include "LevelLoader.h"

int main(int, char* [])
{

	GameEngine::Engine engine("../Data/");
	LevelLoader levelLoader(1);

	bool continueGame = true;

	while (continueGame && levelLoader.HasNextLevel())
	{
		continueGame = engine.Run(levelLoader.GetNextLevelLoader());
	}

	return 0;
}
