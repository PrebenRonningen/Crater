#include "CraterPCH.h"
#include "SpriteRenderComponent.h"

#include "SDL.h"
#include "Crater/GameObject.h"
#include "Crater/Objects/Texture2D.h"
#include "Crater/Managers/ResourceManager.h"
#include "Crater/Renderer.h"

namespace CraterEngine
{
	SpriteRenderComponent::SpriteRenderComponent(const GameObject* parent, const std::string& filePath)
		: Component{ parent }
		, m_pTexture2D{ nullptr }
		, m_TexData{}
		, m_TexturePath{ filePath }
	{		
		if ( !filePath.empty() )
		{
			m_pTexture2D = ResourceManager::GetInstance().LoadTexture(m_TexturePath);
		}
	}

	SpriteRenderComponent::~SpriteRenderComponent()
	{
		if ( m_pTexture2D )
		{
			delete m_pTexture2D;
			m_pTexture2D = nullptr;
		}
	}

	void SpriteRenderComponent::Render() const
	{
		if ( m_pTexture2D )
		{
			const auto& transform = m_pParent->GetComponent<TransformComponent>()->GetPosition();
			Renderer::GetInstance().RenderTexture(*m_pTexture2D, transform.x, transform.y);
		}
	}

	void SpriteRenderComponent::SetTexture(const std::string& filePath)
	{
		if ( m_pTexture2D )
		{
			delete m_pTexture2D;
			m_pTexture2D = ResourceManager::GetInstance().LoadTexture(filePath);
			return;
		}
		m_pTexture2D = ResourceManager::GetInstance().LoadTexture(filePath);
	}
}
