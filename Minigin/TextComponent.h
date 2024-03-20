#pragma once
#include "BaseComponent.h"
#include "IObserver.h"

#include <string>

namespace GameEngine
{
	class Font;
	class Texture2D;
	class TextureComponent;
	class FPS;
	class GameObject;
	class RenderComponent;

	class TextComponent final: public BaseComponent, public IObserver<int>, public IObserver<std::string>
	{
	public:
		TextComponent(GameObject* GOptr) :
			BaseComponent(GOptr),
			m_Text(""),
			m_pFont(),
			m_pTextTexture(nullptr),
			m_pTextureComponent(nullptr) {};

		TextComponent(GameObject* GOptr, std::string text, std::shared_ptr<Font> font);

		void Update() override;

		void SetText(const std::string& text);

		std::string GetText()const
		{
			return m_Text;
		};

		std::shared_ptr<Texture2D> GetTexturePtr() const
		{
			return m_pTextTexture;
		}

		void Notify(const int& message_from_subject) override;
		void Notify(const std::string& message_from_subject) override;

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


