#include "BoxColliderComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "TextureComponent.h"

GameEngine::BoxCollider::BoxCollider(GameObject* pGameObject,int left, int bottom, int width, int height):
	m_RectCollider({left,bottom,width,height}),BaseComponent(pGameObject)
{
    GetGameObject()->AddComponent<TextureComponent>(); 

    m_pTextureComponent = GetGameObject()->GetComponent<TextureComponent>(); 
}

GameEngine::BoxCollider::BoxCollider(GameObject* pGameObject,Rect shape):
	BaseComponent(pGameObject), m_RectCollider(shape)
{
    GetGameObject()->AddComponent<TextureComponent>();

    m_pTextureComponent = GetGameObject()->GetComponent<TextureComponent>(); 
}

bool GameEngine::BoxCollider::IsColliding(const Rect& rectShape, HitInfo& hitInfo) const
{
	const glm::vec2 ray1(rectShape.left, rectShape.bottom + rectShape.height / 2);
	const glm::vec2 ray2(rectShape.left + rectShape.width, rectShape.bottom + rectShape.height / 2);

	const std::vector<glm::vec3> RectPoints = CreatePointsFromRect(rectShape); 

	return Raycast(RectPoints, ray1, ray2, hitInfo); 
}

std::vector<glm::vec3> GameEngine::BoxCollider::CreatePointsFromRect(const Rect& rectShape) const
{
	std::vector<glm::vec3> points;

	points.push_back(glm::vec3(rectShape.left, rectShape.bottom, 0.0f)); // Bottom-left corner
	points.push_back(glm::vec3(rectShape.left + rectShape.width, rectShape.bottom, 0.0f)); // Bottom-right corner
	points.push_back(glm::vec3(rectShape.left + rectShape.width, rectShape.bottom + rectShape.height, 0.0f)); // Top-right corner
	points.push_back(glm::vec3(rectShape.left, rectShape.bottom + rectShape.height, 0.0f)); // Top-left corner

	return points;
}

void GameEngine::BoxCollider::Update()
{
    if (m_pColliderTexture == nullptr)
    {
        CreateTextureFromRect(m_RectCollider.width, m_RectCollider.height, m_Color);
   }
}

void GameEngine::BoxCollider::CreateTextureFromRect(int width, int height, SDL_Color newColor)
{
    // Create a new SDL surface
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    if (surface == nullptr) 
    {
        std::cerr << "not able to create surface" << std::endl;
        return;
    }

    // Fill the surface with the specified color
    SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, newColor.r, newColor.g, newColor.b));

    // Convert the surface to a texture
    SDL_Texture* texture = SDL_CreateTextureFromSurface(GameEngine::Renderer::GetInstance().GetSDLRenderer(), surface);

    if (texture == nullptr)
    {
        // Handle texture creation error
        SDL_FreeSurface(surface);
        std::cerr << "Texture from surface is nullptr" << std::endl;
        return;
    }

    m_pColliderTexture = std::move(std::make_unique<Texture2D>(texture));

    m_pTextureComponent->SetTexture(std::move(m_pColliderTexture));

    // Free the surface
    SDL_FreeSurface(surface);
}


