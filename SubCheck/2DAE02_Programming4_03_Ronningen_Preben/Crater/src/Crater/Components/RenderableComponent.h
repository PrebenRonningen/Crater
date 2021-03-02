#pragma once
#include "Component.h"
#include "SDL.h"
#include <string>
#include "Crater/GameObject.h"
#include "Crater/Objects/Texture2D.h"
#include "Crater/Objects/Text.h"

namespace CraterEngine
{
	class RenderableComponent : public Component
	{
		struct TextureData
		{
			SDL_Rect textureRect{};
		};
	public:
		RenderableComponent(const GameObject* parent, const std::string filePath = "");
		virtual ~RenderableComponent() override;

		#pragma region deleted
		RenderableComponent(const RenderableComponent& other) = delete;
		RenderableComponent(RenderableComponent&& other) = delete;
		RenderableComponent& operator= (const RenderableComponent& other) = delete;
		RenderableComponent& operator= (const RenderableComponent&& other) = delete;
		#pragma endregion

		virtual bool Initialize() override;
		virtual void Update(const float dt) override;
		virtual void Render() const override;
		void SetTexture(const std::string& text);
		void SetTextAndColor(const std::string& text, const SDL_Color& color = { 255, 255, 255 });
		void SetText(const std::string& text);
		std::string GetText() const
		{
			return m_pText->GetText();
		}
		const TextureData& GetTexInfo()
		{
			FillTextureData();
			return m_TexData;
		};
	private:
		void FillTextureData();
		Text* m_pText;
		Texture2D* m_pTexture2D;
		TextureData m_TexData;
		std::string m_TexturePath;
	};
}