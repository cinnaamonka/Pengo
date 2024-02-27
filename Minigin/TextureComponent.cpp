#include "TextureComponent.h"

GameEngine::TextureComponent::TextureComponent(GameObject* GOptr, const std::string& filename) :Component(GOptr), fileName(filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
GameEngine::TextureComponent::TextureComponent(GameObject* GOptr) :Component(GOptr) {};


