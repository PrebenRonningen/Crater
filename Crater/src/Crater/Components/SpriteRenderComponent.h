#pragma once
#include "Component.h"
namespace CraterEngine
{
	class SpriteRenderComponent : public Component
	{
		struct TextureData
		{
			SDL_Rect textureRect{};
		};
	public:
		SpriteRenderComponent(const GameObject* parent, const std::string& filePath = "");
		virtual ~SpriteRenderComponent() override;
	
	#pragma region deleted
		SpriteRenderComponent(const SpriteRenderComponent& other) = delete;
		SpriteRenderComponent(SpriteRenderComponent&& other) = delete;
		SpriteRenderComponent& operator=(const SpriteRenderComponent& other) = delete;
		SpriteRenderComponent& operator=(SpriteRenderComponent&& other) = delete;
	#pragma endregion

		void SetTexture(const std::string& text);
		virtual bool Initialize();
		virtual void Update(const float dt);
		virtual void Render() const override;
	
	protected:
		Texture2D* m_pTexture2D;
		TextureData m_TexData;
		std::string m_TexturePath;
	};
}