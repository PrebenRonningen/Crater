#include "CraterPCH.h"
#include "RenderableComponent.h"
#include "Crater/Managers/ResourceManager.h"
#include "Crater/Renderer.h"

namespace CraterEngine
{
	//TODO: Spliti into SpriteRenderComponent & TextRenderComponent
	RenderableComponent::RenderableComponent(const GameObject* parent)
		: Component(parent)
		, m_pTexture2D{ nullptr }
		, m_TexData{}
	{
		//if ( !filePath.empty() )
		//{
		//	m_pTexture2D = ResourceManager::GetInstance().LoadTexture(m_TexturePath);
		//}
	}

	RenderableComponent::~RenderableComponent()
	{
		//if ( m_pTexture2D )
		//{
		//	delete m_pTexture2D;
		//	m_pTexture2D = nullptr;
		//}
		//if ( m_pText )
		//{
		//	delete m_pText;
		//	m_pText = nullptr;
		//}
	}
	
	bool RenderableComponent::Initialize()
	{
		//if ( m_pText )
		//{
		//	m_pText->Update(0);
		//}
		if(m_IsInitialized ) return true;
		m_IsInitialized = true;
		return true;
	}

	void RenderableComponent::Update(const float /*dt*/)
	{
		//if ( m_pText )
		//{
		//	m_pText->Update(dt);
		//	m_pTexture2D = m_pText->GetTextTexture();
		//}
	}

	void RenderableComponent::Render() const
	{
		if ( uint64_t(m_pTexture2D->GetSDLTexture()) == 0xdddddddddddddddd )
		{
			std::cout << "send Help";
		}

		if ( m_pTexture2D )
		{
			const auto& transform = m_pParent->GetComponent<TransformComponent>()->GetPosition();
			Renderer::GetInstance().RenderTexture(*m_pTexture2D, transform.x, transform.y);
		}
	}

	//void RenderableComponent::SetTexture(const std::string& filePath)
	//{
	//	if ( m_pTexture2D )
	//	{
	//		delete m_pTexture2D;
	//		m_pTexture2D = ResourceManager::GetInstance().LoadTexture(filePath);
	//		return;
	//	}
	//	m_pTexture2D = ResourceManager::GetInstance().LoadTexture(filePath);
	//}

	void RenderableComponent::SetTexture(Texture2D* pTexture)
	{
		//if ( m_pTexture2D )
		//{
		//	delete m_pTexture2D;
		//	m_pTexture2D = pTexture;
		//	return;
		//}
		m_pTexture2D = pTexture;
	}

	void RenderableComponent::FillTextureData()
	{
		SDL_QueryTexture(m_pTexture2D->GetSDLTexture(), NULL, NULL, &m_TexData.textureRect.w, &m_TexData.textureRect.h);
	}
}