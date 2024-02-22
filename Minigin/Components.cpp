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

dae::TextureComponent::TextureComponent(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextComponent::Update(double elapsedSec)
{
	(void)elapsedSec;

	if (m_NeedsUpdate)
	{
		std::string text = {};

		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now

		if (m_GameObject->HasComponent<FPS>() && m_GameObject->HasComponent<TextComponent>() && m_GameObject->HasComponent<RenderComponent>())
		{
			const auto fps = m_GameObject->GetComponent<FPS>()->GetFPS();

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
