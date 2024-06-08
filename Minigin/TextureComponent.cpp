#include "TextureComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"

GameEngine::TextureComponent::TextureComponent(GameObject* GOptr, const std::string& filename,int textureClipAmount)  
	: BaseComponent(GOptr), fileName(filename),
	m_TextureClipAmount(textureClipAmount)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
	
}

GameEngine::TextureComponent::TextureComponent(GameObject* GOptr) 
	: BaseComponent(GOptr), m_Texture(nullptr),
	m_TextureClipAmount(1)
{
	
}


void GameEngine::TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
void GameEngine::TextureComponent::SetTexture(std::shared_ptr<GameEngine::Texture2D>& texture)
{
	m_Texture = texture;
}

void GameEngine::TextureComponent::Scale(float scaleX, float scaleY)
{
	m_ScaleX = scaleX;
	m_ScaleY = scaleY;
}
