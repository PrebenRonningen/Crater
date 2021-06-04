#include "CraterPCH.h"
#include "SpriteComponent.h"

#include "Crater/GameObject.h"
#include "Crater/Managers/ResourceManager.h"

namespace CraterEngine
{
	SpriteComponent::SpriteComponent(const GameObject* parent, const std::string& filePath, const int rows, const int columns)
		: Component(parent)
		, m_pTexture2D{ nullptr }
		, m_TexturePath{ filePath }
		, m_pParentRenderComponent{nullptr}
		, m_TextureInfo{}
		, m_Rows{rows}
		, m_Columns{columns}
	{
		if ( !parent->HasComponent<RenderableComponent>() )
		{
			std::cout << "[Warning] ParentObject needs RenderComponent\n";
		}
		else
		{
			m_pParentRenderComponent = parent->GetComponent<RenderableComponent>();
		}
		if ( !m_TexturePath.empty() )
			SetTexture(m_TexturePath);
	}

	SpriteComponent::~SpriteComponent()
	{
		if ( m_pTexture2D )
		{
			delete m_pTexture2D;
			m_pTexture2D = nullptr;
		}
	}
	
	void SpriteComponent::SetTexture(const std::string& filePath)
	{
		if( filePath.empty() ) 
		{
			std::cout << "[WARNING] No file path provided\n"; 

			return;
		}
		m_TexturePath = filePath;
		if ( m_pTexture2D )
			delete m_pTexture2D;
		
		m_pTexture2D = ResourceManager::GetInstance().LoadTexture(m_TexturePath);
		FillTextureData();
		PassTextureToRenderComponent();
	}

	bool SpriteComponent::Initialize()
	{
		if(m_IsInitialized ) return true;
		if ( m_TexturePath.empty() )
		{
			m_IsInitialized = false;
			return false;
		}

		if ( !m_pTexture2D )
		{
			SetTexture(m_TexturePath);
		}
		m_IsInitialized = true;
		return true;
	}

	void SpriteComponent::SetTextureSource(int row, int col)
	{
		m_TextureInfo.sourceRectange.w = (m_TextureInfo.textureRect.w / m_Columns);
		m_TextureInfo.sourceRectange.h = (m_TextureInfo.textureRect.h / m_Rows);
		m_TextureInfo.sourceRectange.x = m_TextureInfo.sourceRectange.w * ( col % m_Columns );
		m_TextureInfo.sourceRectange.y = m_TextureInfo.sourceRectange.h * ( row % m_Rows );
		m_pParentRenderComponent->SetSourceRect(m_TextureInfo.sourceRectange);
	}

	void SpriteComponent::PassTextureToRenderComponent()
	{
		if ( m_pParentRenderComponent != nullptr )
		{
			m_pParentRenderComponent->SetTexture(m_pTexture2D, m_TextureInfo);
		}
		else
		{
			m_pParentRenderComponent = m_pParent->GetComponent<RenderableComponent>();
			m_pParentRenderComponent->SetTexture(m_pTexture2D, m_TextureInfo);
		}
	}

	void SpriteComponent::FillTextureData()
	{
		auto transform = m_pParent->GetComponent<TransformComponent>();
		SDL_QueryTexture(m_pTexture2D->GetSDLTexture(), NULL, NULL, &m_TextureInfo.textureRect.w, &m_TextureInfo.textureRect.h);
		m_TextureInfo.sourceRectange.w = m_TextureInfo.textureRect.w / m_Columns;
		m_TextureInfo.sourceRectange.h = m_TextureInfo.textureRect.h / m_Rows;
		m_TextureInfo.sourceRectange.x = 0;
		m_TextureInfo.sourceRectange.y = 0;

		//default info
		m_TextureInfo.destinationRectangle.x = int(transform->GetPosition().x);
		m_TextureInfo.destinationRectangle.y = int(transform->GetPosition().y);
		m_TextureInfo.destinationRectangle.w = m_TextureInfo.sourceRectange.w;
		m_TextureInfo.destinationRectangle.h = m_TextureInfo.sourceRectange.h;
	}
}