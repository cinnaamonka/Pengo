#include "TextComponent.h"
#include "FPS.h"

GameEngine::TextComponent::TextComponent(GameObject* GOptr, std::string text, std::shared_ptr<Font> font) :
	Component(GOptr),
	m_Text(text),
	m_pFont(font),
	m_NeedsUpdate(true),
	m_NumberText(0),
	m_pTextTexture(nullptr),
	m_pTextureComponent(nullptr),
	m_pFPSComponent(nullptr),
	m_pRenderComponent(nullptr)
{
	const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_pTextTexture = std::make_shared<Texture2D>(texture);

	GetGameObject()->AddComponent<TextureComponent>();

	m_pTextureComponent = GetGameObject()->GetComponent<TextureComponent>();
	m_pTextureComponent->SetTexture(m_pTextTexture);

	if (GetGameObject()->HasComponent<FPS>())
	{
		m_pFPSComponent = GetGameObject()->GetComponent<FPS>();
	}

	if (GetGameObject()->HasComponent<RenderComponent>())
	{
		m_pRenderComponent = GetGameObject()->GetComponent<RenderComponent>();
	}
	else
	{
		GetGameObject()->AddComponent<RenderComponent>();
		m_pRenderComponent = GetGameObject()->GetComponent<RenderComponent>();
	}
}

void GameEngine::TextComponent::Update()
{

	if (m_NeedsUpdate)
	{
		std::string text = {};

		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now

		if (m_pFPSComponent != nullptr)
		{
			const auto fps = m_pFPSComponent->GetAverageFPS();

			if (m_Text.size())
			{
				std::ostringstream oss;
				oss << std::fixed << std::setprecision(1) << fps;

				text = oss.str() + " " + m_Text;
			}
			else if (!m_Text.size())
			{
				std::ostringstream oss;
				oss << std::fixed << std::setprecision(1) << fps;

				text = oss.str();
			}

		}
		else if (m_pRenderComponent != nullptr)
		{
			text = m_Text;
		}
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		*m_pTextTexture = Texture2D(texture);

		m_pTextureComponent->SetTexture(m_pTextTexture);
	}
}

void GameEngine::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}


