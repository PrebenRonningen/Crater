#pragma once
#include "Component.h"
#include "Crater/Objects/Text.h"

namespace CraterEngine
{
	class RenderableComponent;
	class GameObject;
	class TextComponent final : public Component
	{
	public:
		TextComponent(const GameObject* parent, const std::string& text = "", const SDL_Color& color = { 255, 255, 255 });
		virtual ~TextComponent();

#pragma region deleted
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
#pragma endregion

		//void SetTexture(const std::string & filePath);
		void SetTextAndColor(const std::string& text, const SDL_Color& color = { 255, 255, 255 });
		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);
		std::string GetText() const
		{
			return m_pText->GetText();
		}

		virtual bool Initialize() override;
		virtual void Update(const float dt) override
		{
			if ( m_pText )
			{
				m_pText->Update(dt);
				m_pTexture2D = m_pText->GetTextTexture();
			}
		};
		
	private:
		void PassTextureToRenderComponent();

		Texture2D* m_pTexture2D;
		std::string m_TextString;
		Text* m_pText;
		RenderableComponent* m_pParentRenderComponent;
		SDL_Color m_Color;
	};
}

