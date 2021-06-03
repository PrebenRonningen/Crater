#include "CraterPCH.h"
#include "SpriteComponent.h"

#include "RenderableComponent.h"
#include "Crater/GameObject.h"
#include "Crater/Managers/ResourceManager.h"

namespace CraterEngine
{
	SpriteComponent::SpriteComponent(const GameObject* parent, const std::string& filePath)
		: Component(parent)
		, m_pTexture2D{ nullptr }
		, m_TexturePath{ filePath }
		, m_pParentRenderComponent{nullptr}
	{
		if ( !parent->HasComponent<RenderableComponent>() )
		{
			std::cout << "[Warning] ParentObject needs RenderComponent\n";
		}
		else
		{
			m_pParentRenderComponent = parent->GetComponent<RenderableComponent>();
			SetTexture(m_TexturePath);
		}
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
		m_TexturePath = filePath;
		if ( m_pTexture2D )
		{
			delete m_pTexture2D;
			m_pTexture2D = ResourceManager::GetInstance().LoadTexture(m_TexturePath);
			PassTextureToRenderComponent();
			return;
		}
		m_pTexture2D = ResourceManager::GetInstance().LoadTexture(m_TexturePath);

		PassTextureToRenderComponent();
	}

	bool SpriteComponent::Initialize()
	{
		if(m_IsInitialized ) return true;
		if ( !m_pTexture2D )
			SetTexture(m_TexturePath);
		m_IsInitialized = true;
		return true;
	}

	void SpriteComponent::PassTextureToRenderComponent()
	{
		if ( m_pParentRenderComponent != nullptr )
		{
			m_pParentRenderComponent->SetTexture(m_pTexture2D);
		}
		else
		{
			m_pParentRenderComponent = m_pParent->GetComponent<RenderableComponent>();
			m_pParentRenderComponent->SetTexture(m_pTexture2D);
		}
	}
}