#include "pch.h"
#include "TextureComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"

GameEngine::TextureComponent::TextureComponent(GameObject* GOptr, const std::string& filename) 
	: BaseComponent(GOptr), fileName(filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}

GameEngine::TextureComponent::TextureComponent(GameObject* GOptr) 
	: BaseComponent(GOptr), m_Texture(nullptr)
{

}

std::shared_ptr<GameEngine::Texture2D> GameEngine::TextureComponent::GetTexture() const
{
	return m_Texture;
}

void GameEngine::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
void GameEngine::TextureComponent::SetTexture(std::shared_ptr<GameEngine::Texture2D> texture)
{
	m_Texture = texture;
}