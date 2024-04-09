#include <Engine.h>
#include "Game.h"

void load()
{
	std::unique_ptr<Game> pGame = std::make_unique<Game>();
	pGame->Initialize();

}

int main(int, char* [])
{

	GameEngine::Engine engine("../Data/");
	engine.Run(load);

	return 0;
}
