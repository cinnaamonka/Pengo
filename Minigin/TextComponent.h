#pragma once
#include "BaseComponent.h"

#include <string>

namespace GameEngine
{
	class Font;
	class Texture2D;
	class TextureComponent;
	class GameObject;

	class TextComponent final: public BaseComponent
	{
	public:
		TextComponent(GameObject* GOptr) :
			BaseComponent(GOptr),
			m_Text(""),
			m_pFont(),
			m_pTextTexture(nullptr),
			m_pTextureComponent(nullptr) {};

		TextComponent(GameObject* GOptr, std::string text, std::shared_ptr<Font> font);
		TextComponent(GameObject* GOptr, std::shared_ptr<Font> font); 
	
		~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update() override;

		void SetText(const std::string& text);

		const std::string& GetText()const
		{
			return m_Text;
		};

		void AddAdditionalText(std::string text)
		{
			m_AdditionalText = text;
		}

	private:
		std::string m_Text;
		std::string m_AdditionalText;
		std::string m_CurrentText;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTextTexture;

		TextureComponent* m_pTextureComponent;
	};
}


