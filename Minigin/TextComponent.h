#pragma once
#include "BaseComponent.h"

namespace GameEngine
{
	class Font;
	class Texture2D;
	class TextureComponent;
	class FPS;
	class RenderComponent;

	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(GameObject* GOptr) :
			BaseComponent(GOptr),
			m_Text(""),
			m_pFont(),
			m_NeedsUpdate(true),
			m_NumberText(0),
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
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::string m_CurrentText;
		double* m_NumberText;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTextTexture;

		TextureComponent* m_pTextureComponent;
	};
}


