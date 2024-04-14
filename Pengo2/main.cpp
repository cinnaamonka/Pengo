#include <Engine.h>
#include "Game.h"

std::unique_ptr<Game> load()
{
    std::unique_ptr<Game> pGame = std::make_unique<Game>();
    pGame->Initialize();

    return pGame;
}

int main(int, char* [])
{

	GameEngine::Engine engine("../Data/");
	engine.Run(load);



	return 0;
}
