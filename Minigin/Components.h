#pragma once
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"
#include <memory>
#include <stdexcept>
#include <SDL_ttf.h>
class Component
{
public:
    virtual void Update(dae::GameObject& gameObject ) = 0; 
    virtual void Render(dae::GameObject& gameObject) const = 0; 
    virtual ~Component() = default;
};
class TextureComponent : public Component 
{
public:
    TextureComponent(std::shared_ptr<dae::Texture2D> texture) : m_Texture(texture) {}
    TextureComponent() {};
    void Update(dae::GameObject& gameObject) override;
    void Render(dae::GameObject& gameObject) const override;
private:
    std::shared_ptr<dae::Texture2D> m_Texture;
};

class RenderComponent : public Component
{
public:
    void Update(dae::GameObject& gameObject) override;
    void Render(dae::GameObject& gameObject) const override;
};
class TextComponent : public Component
{
public:
    void Update(dae::GameObject& gameObject) override;
    void Render(dae::GameObject& gameObject) const override;
};
class Transform : public Component
{
public:
    Transform() : m_position(0.0f, 0.0f, 0.0f) {};

    const glm::vec3& GetPosition() const { return m_position; };
    void SetPosition(float x, float y, float z);

private:
    glm::vec3 m_position;
};

