#pragma once
#include "Component.h"
#include "SDL.h"
#include <string>
#include "Crater/GameObject.h"
#include "Crater/Objects/Text.h"

namespace CraterEngine
{

	//class RenderableComponent final : public Component
	//{
	////public:
	//	RenderableComponent(const GameObject* parent);
	//	virtual ~RenderableComponent() override;
	//
	//	#pragma region deleted
	//	RenderableComponent(const RenderableComponent& other) = delete;
	//	RenderableComponent(RenderableComponent&& other) = delete;
	//	RenderableComponent& operator= (const RenderableComponent& other) = delete;
	//	RenderableComponent& operator= (const RenderableComponent&& other) = delete;
	//	#pragma endregion
	//
	//	virtual bool Initialize() override;
	//	virtual void Update(const float dt) override;
	//	virtual void Render() const override;
	//
	//	void SetTexture(Texture2D* pTexture);
	//	void SetTexture(Texture2D* pTexture, const TextureData& textureData);
	//	void UpdateDestination();
	//	void SetSourceRect(const SDL_Rect& srcRect);
	//
	//	const TextureData& GetTexInfo()
	//	{
	//		FillTextureData();
	//		return m_TexData;
	//	};
//	//private:
	//	void FillTextureData();
	//	Texture2D* m_pTexture2D;
	//	TextureData m_TexData;
	//};
}