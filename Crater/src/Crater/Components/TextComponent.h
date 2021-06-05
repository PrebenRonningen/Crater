#pragma once
#include "Component.h"
#include "Crater/Objects/Text.h"

namespace CraterEngine
{
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

		virtual bool Initialize() override;
		virtual void Update(const float dt) override;
		virtual void Render() const override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);
		void SetTextAndColor(const std::string& text, const SDL_Color& color = { 255, 255, 255 });
		std::string GetText() const
		{
			return m_pText->GetText();
		}
		const TextureData& GetTexInfo()
		{
			return m_TextureInfo;
		};
	private:
		void FillTextureData();
		Texture2D* m_pTexture2D;
		std::string m_TextString;
		TextureData m_TextureInfo;
		Text* m_pText;
		SDL_Color m_Color;
	};
}

