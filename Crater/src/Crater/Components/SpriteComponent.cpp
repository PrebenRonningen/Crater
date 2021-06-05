#include "CraterPCH.h"
#include "SpriteComponent.h"

#include "Crater/GameObject.h"
#include "Crater/Managers/ResourceManager.h"
#include "Crater/Renderer.h"

namespace CraterEngine
{
	SpriteComponent::SpriteComponent(const GameObject* parent, const std::string& filePath, const int rows, const int columns)
		: Component(parent)
		, m_pTexture2D{ nullptr }
		, m_TexturePath{ filePath }
		, m_TextureInfo{}
		, m_Rows{rows}
		, m_Columns{columns}
	{
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
	
	bool SpriteComponent::Initialize()
	{
		if( m_IsInitialized ) return true;
		if ( m_TexturePath.empty() )
		{
			m_IsInitialized = false;
			std::cout << "[WARNING] No file path provided\n";
			return false;
		}

		if ( !m_pTexture2D )
		{
			SetTexture(m_TexturePath);
		}

		UpdateDestination();
		m_IsInitialized = true;
		return true;
	}

	void SpriteComponent::Render() const
	{
		if ( m_pTexture2D )
		{
			Renderer::GetInstance().RenderTexture(*m_pTexture2D, m_TextureInfo.destinationRectangle, m_TextureInfo.sourceRectange);
		}
	}

	void SpriteComponent::SetTexture(const std::string& filePath)
	{
		if ( filePath.empty() )
		{
			std::cout << "[WARNING] No file path provided\n";
			return;
		}
		m_TexturePath = filePath;

		if ( m_pTexture2D )
			delete m_pTexture2D;

		m_pTexture2D = ResourceManager::GetInstance().LoadTexture(m_TexturePath);
		FillTextureData();
	}

	void SpriteComponent::SetTextureSource(int row, int col)
	{
		m_TextureInfo.sourceRectange.w = ( m_TextureInfo.textureRect.w / m_Columns );
		m_TextureInfo.sourceRectange.h = ( m_TextureInfo.textureRect.h / m_Rows );
		m_TextureInfo.sourceRectange.x = m_TextureInfo.sourceRectange.w * ( col % m_Columns );
		m_TextureInfo.sourceRectange.y = m_TextureInfo.sourceRectange.h * ( row % m_Rows );
	}

	void SpriteComponent::SetDestination(int x, int y)
	{
		const auto& transform = m_pParent->GetComponent<TransformComponent>();
		m_TextureInfo.destinationRectangle.x = int(transform->GetPosition().x) + x;
		m_TextureInfo.destinationRectangle.y = int(transform->GetPosition().y) + y;
	}

	void SpriteComponent::UpdateDestination()
	{
		const auto& transform = m_pParent->GetComponent<TransformComponent>();
		m_TextureInfo.destinationRectangle.x = int(transform->GetPosition().x);
		m_TextureInfo.destinationRectangle.y = int(transform->GetPosition().y);

		m_TextureInfo.destinationRectangle.w = int(m_TextureInfo.sourceRectange.w * transform->GetScale().x);
		m_TextureInfo.destinationRectangle.h = int(m_TextureInfo.sourceRectange.h * transform->GetScale().y);
	}

	void SpriteComponent::GetRowAndCol(int& row, int& col) const
	{
		float column = float(m_TextureInfo.sourceRectange.x) / m_TextureInfo.textureRect.w;
		float rw = float(m_TextureInfo.sourceRectange.y) / m_TextureInfo.textureRect.h;

		col = int(column * m_Columns);
		row = int(rw * m_Rows);
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
		m_TextureInfo.destinationRectangle.w = int(m_TextureInfo.sourceRectange.w * transform->GetScale().x);
		m_TextureInfo.destinationRectangle.h = int(m_TextureInfo.sourceRectange.h * transform->GetScale().y);
	}
}