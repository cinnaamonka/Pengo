#pragma once
#include "Font.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include <memory>
#include <iostream>
#include <stdexcept>
#include <SDL_ttf.h>
#include <glm/glm.hpp>
#include "GameObject.h"
namespace dae
{
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;
	};
	class TextureComponent : public Component
	{
	public:
		TextureComponent(std::shared_ptr<dae::Texture2D> texture) : m_Texture(texture) {}
		TextureComponent() {};


		TextureComponent(const TextureComponent& other)
			: m_Texture(other.m_Texture)
		{

		}


		TextureComponent& operator=(const TextureComponent& other)
		{
			if (this != &other) {
				m_Texture = other.m_Texture;
			}
			return *this;
		}

		std::shared_ptr<dae::Texture2D> GetTexture() const
		{
			return m_Texture;
		}

		void SetTexture(const std::string& filename)
		{
			m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
		}

	private:
		std::shared_ptr<dae::Texture2D> m_Texture;
	};
	class TransformComponent : public Component
	{
	public:
		TransformComponent() : m_Position(0.0f, 0.0f, 0.0f) {};

		TransformComponent(glm::vec3 pos) : m_Position(pos) {}

		TransformComponent(const TransformComponent& other)
			: m_Position(other.m_Position)
		{

		}

		TransformComponent& operator=(const TransformComponent& other)
		{
			if (this != &other) {
				m_Position = other.m_Position;

			}
			return *this;
		}

		const glm::vec3& GetPosition() const
		{
			return m_Position;
		}

		void SetPosition(float x, float y, float z)
		{
			m_Position.x = x;
			m_Position.y = y;
			m_Position.z = z;
		}

	private:
		glm::vec3 m_Position;
	};

	class RenderComponent : public Component
	{
	public:
		RenderComponent() :
			m_Position(0, 0, 0), m_Texture{}
		{

		};
		RenderComponent(std::shared_ptr<Texture2D> texture, const glm::vec3& pos)
			: m_Texture(texture), m_Position(pos)
		{
		}

		~RenderComponent() {}

		void Render() const
		{
			if (m_Texture != nullptr)
			{
				Renderer::GetInstance().RenderTexture(*m_Texture, m_Position.x, m_Position.y);
			}
		}

		void SetTexture(std::shared_ptr<Texture2D> texture)
		{
			m_Texture = texture;
		}
		void SetPosition(const glm::vec3& pos)
		{
			m_Position = pos;
		}

		glm::vec3 GetPosition() const
		{
			return m_Position;
		}

	private:
		std::shared_ptr<Texture2D> m_Texture;
		glm::vec3 m_Position;
	};

	class TextComponent : public Component
	{
	public:
		TextComponent():m_Text(""),m_Font(),m_NeedsUpdate(true), m_NumberText(0), m_TextTexture(nullptr) {};
		TextComponent(std::string text, std::shared_ptr<Font> font) :m_Text(text), m_Font(font), m_NeedsUpdate(true), m_NumberText(0), m_TextTexture(nullptr)
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
			/*m_NeedsUpdate = false;*/
		}
		TextComponent(double* numberText, std::shared_ptr<Font> font) :m_Text(""), m_Font(font), m_NeedsUpdate(true), m_NumberText(numberText),
			m_TextTexture(nullptr)
		{
			const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
			const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), std::to_string(*m_NumberText).c_str(), color);

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
			/*m_NeedsUpdate = false;*/
		}
		void Update()
		{
			if (m_NeedsUpdate)
			{
				auto text = !m_Text.size() ? std::to_string(*m_NumberText) : m_Text;

				const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
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
		};
		void SetText(const std::string& text)
		{
			m_Text = text;
			m_NeedsUpdate = true;
		};

		std::shared_ptr<Texture2D> GetTexturePtr() const
		{
			return m_TextTexture;
		}
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		double* m_NumberText;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_TextTexture;
	};

	class FPS : public Component
	{
	public:
		FPS() : fps(std::make_shared<double>(0.0)) {}

		virtual void Update(double elapsedSec)
		{
			*fps = 1.0 / elapsedSec;
		}

		~FPS() {}

		double* GetFPSPtr() const
		{
			return fps.get();
		}

	private:
		std::shared_ptr<double> fps;
	};

}




