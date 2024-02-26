#pragma once
#include "Font.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include <memory>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <SDL_ttf.h>
#include <glm/glm.hpp>
#include "GameObject.h"

class GameObject;

namespace dae
{
	class Component
	{
	public:
		
		Component() :m_GameObject(nullptr) {};

		Component(GameObject* GOptr) :m_GameObject(GOptr) {};

		virtual void Update(double elapsedSec) 
		{
			(void)elapsedSec;
		};

		GameObject* GetGameObject() const
		{
			return m_GameObject;
		}

		virtual void Render() const {};
		virtual ~Component() {};

		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;
	
	protected:
		GameObject* m_GameObject;
	};

	class TextureComponent : public Component
	{
	public:
		TextureComponent(GameObject* GOptr, const std::string& filename) :Component(GOptr), fileName(filename)
		{
			m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
		};
		TextureComponent(GameObject* GOptr) :Component(GOptr) {};

		std::shared_ptr<dae::Texture2D> GetTexture() const
		{
			return m_Texture;
		}

		void SetTexture(const std::string& filename)
		{
			m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
		}
		void SetTexture(std::shared_ptr<dae::Texture2D> texture)
		{
			m_Texture = texture; 
		}

	private:
		std::shared_ptr<dae::Texture2D> m_Texture;
		std::string fileName;
	};

	class TransformComponent : public Component
	{
	public:
		TransformComponent(GameObject* GOptr) : Component(GOptr), m_Position(0.0f, 0.0f, 0.0f) {};

		TransformComponent(GameObject* GOptr, glm::vec3 pos) : Component(GOptr), m_Position(pos){}

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
		RenderComponent(GameObject* GOptr) : Component(GOptr), m_Position(0, 0, 0), m_Texture(nullptr){};

		void Render() const override;

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

		std::shared_ptr<Texture2D> GetTexture()
		{
			return m_Texture;
		}

	private:
		std::shared_ptr<Texture2D> m_Texture;
		glm::vec3 m_Position;
	};

	class TextComponent : public Component
	{
	public:
		TextComponent(GameObject* GOptr):Component(GOptr),m_Text(""),m_Font(),m_NeedsUpdate(true), m_NumberText(0), m_TextTexture(nullptr) {};
		TextComponent(GameObject* GOptr, std::string text, std::shared_ptr<Font> font);
		
		void Update(double elapsedSec) override;
		
		void SetText(const std::string& text);
		
		std::string GetText()const
		{
			return m_Text;
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
		FPS(GameObject* GOptr) : Component(GOptr),fps(0.0) {}

		void Update(double elapsedSec) override;

		double GetFPS() const
		{
			return fps;
		}

	private:
		double fps;
	};

}




