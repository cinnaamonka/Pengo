#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"

#define IMGUI_DEFINE_MATH_OPERATORS
#include <../imgui/imgui.h>
#include <../imgui/backends/imgui_impl_sdl2.h>
#include <../imgui/backends/imgui_impl_opengl3.h>
#include <../imgui/imgui_plot.h>


#include <stdexcept>
#pragma warning( disable : 4244 )

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void GameEngine::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
}

void GameEngine::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	SceneManager::GetInstance().Render();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);
}

void GameEngine::Renderer::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void GameEngine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void GameEngine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const Rect& destDimensions, bool movingRight) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(destDimensions.width);
	dst.h = static_cast<int>(destDimensions.height);

	SDL_Rect src{};
	src.x = destDimensions.left;
	src.y = destDimensions.bottom;
	src.w = static_cast<int>(destDimensions.width);
	src.h = static_cast<int>(destDimensions.height);

	if (movingRight)
	{
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst);
	}
	else
	{
		SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;

		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, 0, nullptr, flip);
	}

}

SDL_Renderer* GameEngine::Renderer::GetSDLRenderer() const { return m_renderer; }
