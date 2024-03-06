#include "../pch.h"

#include "Engine.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Time.h"
#include "General.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

GameEngine::Engine::Engine(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		General::TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		General::WINDOW_WIDTH,
		General::WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

GameEngine::Engine::~Engine()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void GameEngine::Engine::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();

	while (doContinue)
	{
		// Update time 
		GameEngine::Time::Update();
		m_Lag += GameEngine::Time::GetElapsed();
		
		// handle user input
		doContinue = input.ProcessInput();

		while (m_Lag >= GameEngine::General::FIXED_TIME_STEP)
		{
			// fixed update here
			m_Lag -= GameEngine::General::FIXED_TIME_STEP;
		}
		// Update
		sceneManager.Update();

		// late update for camera 
		
		//render(lag / MS_PER_UPDATE); 
		// i dont know if should be implemented
		
		// render
		renderer.Render();

		// clean up( should be decent)
		sceneManager.Cleanup();

		const auto ms_per_frame = std::chrono::milliseconds(1000) / GameEngine::General::TARGET_FPS;

		const auto sleepTime = Time::GetCurrent() + std::chrono::milliseconds(ms_per_frame) - std::chrono::high_resolution_clock::now();

		std::this_thread::sleep_for(sleepTime); 
	}

}
