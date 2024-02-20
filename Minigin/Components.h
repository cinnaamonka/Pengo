#pragma once
#include "Font.h"
#include "Texture2D.h"

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

        std::shared_ptr<dae::Texture2D> GetTexture() const
        {
            return m_Texture;
        }

        void SetTexture(std::shared_ptr<dae::Texture2D> texture)
        {
            m_Texture = texture;
        }
    private:
        std::shared_ptr<dae::Texture2D> m_Texture;
    };

    class TransformComponent : public Component
    {
    public:
        TransformComponent() : m_Position(0.0f, 0.0f, 0.0f) {};

        const glm::vec3& GetPosition() const
        { 
            return m_Position;
        };

        void SetPosition(float x, float y, float z)
        {
            m_Position.x = x;
            m_Position.y = y;
            m_Position.z = z;
        }
 ;

    private:
        glm::vec3 m_Position;  
    };

    class RenderComponent : public Component
    {
    public:
        
        RenderComponent(TextureComponent* textureComponent, TransformComponent* transformComponent)
            : m_TextureComponent(textureComponent), m_TransformComponent(transformComponent) {
          
        }

        ~RenderComponent() { }

        void Render() const
        {
            const auto& pos = m_TransformComponent->GetPosition();
            Renderer::GetInstance().RenderTexture(*m_TextureComponent->GetTexture(), pos.x, pos.y);
        }

    private:
        TextureComponent* m_TextureComponent;
        TransformComponent* m_TransformComponent;
    };
}



//class TextComponent : public Component
//{
//public:
//    void Update(dae::GameObject& gameObject) override;
//    void Render(dae::GameObject& gameObject) const override;
//};


