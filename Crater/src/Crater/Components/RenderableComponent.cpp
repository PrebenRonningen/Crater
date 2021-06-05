#include "CraterPCH.h"
#include "RenderableComponent.h"
#include "Crater/Managers/ResourceManager.h"
#include "Crater/Renderer.h"

namespace CraterEngine
{
	//RenderableComponent::RenderableComponent(const GameObject* parent)
	//	: Component(parent)
	//	, m_pTexture2D{ nullptr }
	//	, m_TexData{}
	//{
	//}
	//
	//RenderableComponent::~RenderableComponent()
	//{
	//}
	//
	//bool RenderableComponent::Initialize()
	//{
	//	if(m_IsInitialized ) return true;
	//	UpdateDestination();
	//	m_IsInitialized = true;
	//	return true;
	//}

	//void RenderableComponent::Update(const float /*dt*/)
	//{
	//}

	//void RenderableComponent::Render() const
	//{
	//	if ( m_pTexture2D )
	//	{
	//		Renderer::GetInstance().RenderTexture(*m_pTexture2D, m_TexData.destinationRectangle, m_TexData.sourceRectange);
	//	}
	//}

	//void RenderableComponent::SetTexture(Texture2D* pTexture)
	//{
	//	if ( pTexture != nullptr )
	//	{
	//		m_pTexture2D = pTexture;
	//		FillTextureData();
	//	}
	//}

	//void RenderableComponent::SetTexture(Texture2D* pTexture, const TextureData& textureData)
	//{
	//	if ( pTexture != nullptr )
	//	{
	//		m_pTexture2D = pTexture;
	//		m_TexData = textureData;
	//	}
	//}

	//void RenderableComponent::UpdateDestination()
	//{
	//	const auto& transform = m_pParent->GetComponent<TransformComponent>();
	//	m_TexData.destinationRectangle.x = int(transform->GetPosition().x);
	//	m_TexData.destinationRectangle.y = int(transform->GetPosition().y);

	//	m_TexData.destinationRectangle.w = int(m_TexData.sourceRectange.w * transform->GetScale().x);
	//	m_TexData.destinationRectangle.h = int(m_TexData.sourceRectange.h * transform->GetScale().y);
	//	
	//}

	/*void RenderableComponent::SetSourceRect(const SDL_Rect& srcRect)
	{
		m_TexData.sourceRectange = srcRect;
	}*/

	//void RenderableComponent::FillTextureData()
	//{
	//	SDL_QueryTexture(m_pTexture2D->GetSDLTexture(), NULL, NULL, &m_TexData.textureRect.w, &m_TexData.textureRect.h);
	//	m_TexData.destinationRectangle.w = m_TexData.sourceRectange.w = m_TexData.textureRect.w;
	//	m_TexData.destinationRectangle.h = m_TexData.sourceRectange.h = m_TexData.textureRect.h;
	//}
}