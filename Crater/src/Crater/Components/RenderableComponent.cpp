#include "CraterPCH.h"
#include "RenderableComponent.h"
#include "Crater/Managers/ResourceManager.h"
#include "Crater/Renderer.h"

namespace CraterEngine
{
	//TODO: Spliti into SpriteRenderComponent & TextRenderComponent
	RenderableComponent::RenderableComponent(const GameObject* parent, const std::string filePath)
		: Component(parent)
		, m_pText{nullptr}
		, m_pTexture2D{ nullptr }
		, m_TexData{}
		, m_TexturePath{filePath}
	{
		if ( !filePath.empty() )
		{
			m_pTexture2D = ResourceManager::GetInstance().LoadTexture(m_TexturePath);
		}
	}

	RenderableComponent::~RenderableComponent()
	{
		if ( m_pTexture2D )
		{
			delete m_pTexture2D;
			m_pTexture2D = nullptr;
		}
		if ( m_pText )
		{
			delete m_pText;
			m_pText = nullptr;
		}
	}
	
	bool RenderableComponent::Initialize()
	{
		if ( m_pText )
		{
			m_pText->Update(0);
		}
		return true;
	}

	void RenderableComponent::Update(const float dt)
	{
		if ( m_pText )
		{
			m_pText->Update(dt);
			m_pTexture2D = m_pText->GetTextTexture();
		}
	}

	void RenderableComponent::Render() const
	{
		if ( m_pTexture2D )
		{
			const auto& transform = m_pParent->GetComponent<TransformComponent>()->GetPosition();
			Renderer::GetInstance().RenderTexture(*m_pTexture2D, transform.x, transform.y);
		}
	}
	void RenderableComponent::SetTexture(const std::string& filePath)
	{
		if ( m_pTexture2D )
		{
			delete m_pTexture2D;
			m_pTexture2D = ResourceManager::GetInstance().LoadTexture(filePath);
			return;
		}
		m_pTexture2D = ResourceManager::GetInstance().LoadTexture(filePath);
	}

	void RenderableComponent::SetTextAndColor(const std::string& text, const SDL_Color& color)
	{
		if ( !m_pText )
		{
			m_pText = new Text("0", ResourceManager::GetInstance().LoadFont("Lingua.otf", 30));
			m_pText->SetTextAndColor(text,color);
			m_pText->Update(0);
			m_pTexture2D = m_pText->GetTextTexture();
			return;
		}
		m_pText->SetTextAndColor(text, color);
		m_pText->Update(0);
		m_pTexture2D = m_pText->GetTextTexture();
	}

	void RenderableComponent::SetText(const std::string& text)
	{
		if ( m_pText )
		{
			m_pText->SetText(text);
		}
	}
	void RenderableComponent::FillTextureData()
	{
		SDL_QueryTexture(m_pTexture2D->GetSDLTexture(), NULL, NULL, &m_TexData.textureRect.w, &m_TexData.textureRect.h);
	}
}