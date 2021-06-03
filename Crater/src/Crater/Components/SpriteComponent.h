#pragma once
#include "Component.h"
#include "Crater/Objects/Texture2D.h"

namespace CraterEngine
{
	class RenderableComponent;
	class GameObject;
	class SpriteComponent : public Component
	{
	public:
		SpriteComponent(const GameObject* parent, const std::string& filePath = "");
		virtual ~SpriteComponent();

		void SetTexture(const std::string& filePath);
		virtual bool Initialize() override;
		virtual void Update(const float ) override{};
	private:
		void PassTextureToRenderComponent();

		Texture2D* m_pTexture2D;
		std::string m_TexturePath;
		RenderableComponent* m_pParentRenderComponent;
	};
}