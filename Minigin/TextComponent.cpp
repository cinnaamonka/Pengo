#include "pch.h"

#include "TextComponent.h"
#include "TextureComponent.h"
#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"

GameEngine::TextComponent::TextComponent(GameObject* GOptr, std::string text, std::shared_ptr<Font> font) :
	BaseComponent(GOptr),
	m_Text(text),
	m_pFont(font),
	m_pTextTexture(nullptr),
	m_pTextureComponent(nullptr)
{
	GetGameObject()->AddComponent<TextureComponent>();

	m_pTextureComponent = GetGameObject()->GetComponent<TextureComponent>();

	Update();

	if (m_pTextTexture != nullptr)
	{
		m_pTextureComponent->SetTexture(m_pTextTexture);
	}
}

void GameEngine::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	Update();
}

void GameEngine::TextComponent::Update()
{	
	if (m_Text != m_CurrentText || m_pTextTexture == nullptr)
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

		m_CurrentText = m_Text;


		m_pTextureComponent->SetTexture(m_pTextTexture);
	}

	if (m_Text.empty())
	{
		m_pTextTexture = nullptr;
	}
		
}


