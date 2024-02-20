#pragma once
#include "Font.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include <memory>
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
        /* virtual void Update(dae::GameObject& gameObject) = 0;
         virtual void Render(dae::GameObject& gameObject) const = 0; */
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
        RenderComponent(): 
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
}



//class TextComponent : public Component
//{
//public:
//    void Update(dae::GameObject& gameObject) override;
//    void Render(dae::GameObject& gameObject) const override;
//};


