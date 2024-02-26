#include "Components.h"

#include "GameObject.h"

dae::Component::~Component()
{

}

void dae::RenderComponent::Render() const
{
	if (m_GameObject->HasComponent<TextureComponent>() && m_GameObject->HasComponent<TransformComponent>())
	{
		const auto& newTexture = m_GameObject->GetComponent<TextureComponent>()->GetTexture();
		const auto& position = m_GameObject->GetComponent<TransformComponent>()->GetPosition();

		if (newTexture != nullptr)
		{
			Renderer::GetInstance().RenderTexture(*newTexture, position.x, position.y);
		}
	}

	if (m_GameObject->HasComponent<TextComponent>() && m_GameObject->HasComponent<TransformComponent>())
	{
		const auto& newTextComponent = m_GameObject->GetComponent<TextComponent>()->GetTexturePtr();
		const auto& position = m_GameObject->GetComponent<TransformComponent>()->GetPosition();

		if (newTextComponent != nullptr)
		{
			Renderer::GetInstance().RenderTexture(*newTextComponent, position.x, position.y);
		}
	}
}

dae::TextComponent::TextComponent(std::string text, std::shared_ptr<Font> font):m_Text(text), m_Font(font), m_NeedsUpdate(true), m_NumberText(0), m_TextTexture(nullptr)
{
	const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
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
	m_TextTexture = std::make_shared<Texture2D>(texture);
}

void dae::TextComponent::Update(double elapsedSec)
{
	(void)elapsedSec;

	if (m_NeedsUpdate)
	{
		std::string text = {};

		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now

		if (m_GameObject->HasComponent<FPS>() && m_GameObject->HasComponent<RenderComponent>())
		{
			const auto fps = m_GameObject->GetComponent<FPS>()->GetFPS() ;

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

			else if (m_GameObject->HasComponent<TextComponent>() && m_GameObject->HasComponent<RenderComponent>())
			{
				text = m_Text;
			}

			const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), text.c_str(), color);
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
			*m_TextTexture = Texture2D(texture);
		}
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::FPS::Update(double elapsedSec)
{
	fps = 1.0 / elapsedSec;

}
