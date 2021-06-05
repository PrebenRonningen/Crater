#include "CraterPCH.h"
#include "TextComponent.h"
#include "Crater/Managers/ResourceManager.h"
#include "Crater/Renderer.h"
#include "RenderableComponent.h"
namespace CraterEngine
{
	TextComponent::TextComponent(const GameObject* parent, const std::string& text, const SDL_Color& color)
		:Component(parent)
		, m_pTexture2D{nullptr}
		, m_TextString{text}
		, m_pText{nullptr}
		, m_Color{ color }
	{		
		if(!m_TextString.empty() )
			SetTextAndColor(m_TextString, m_Color);
	}

	TextComponent::~TextComponent()
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

	bool TextComponent::Initialize()
	{
		if ( m_IsInitialized ) return true;
		if ( !m_pTexture2D )
			SetTextAndColor(m_TextString, m_Color);
		m_IsInitialized = true;
		return true;
	}
	void TextComponent::Update(const float dt)
	{
		if ( m_pText )
		{
			m_pText->Update(dt);
			m_pTexture2D = m_pText->GetTextTexture();
		}
	}
	
	void TextComponent::Render() const
	{
		if ( m_pTexture2D )
		{
			auto& transform = m_pParent->GetComponent<TransformComponent>()->GetPosition();
			Renderer::GetInstance().RenderTexture(*m_pTexture2D, transform.x, transform.y);
		}
	}

	void TextComponent::SetTextAndColor(const std::string& text, const SDL_Color& color)
	{
		m_Color = color;
		if( !text.empty() )
			m_TextString = text;
		else 
			m_TextString = " ";
		if ( !m_pText )
		{
			m_pText = new Text(m_TextString, ResourceManager::GetInstance().LoadFont("Lingua.otf", 30));
		}

		m_pText->SetTextAndColor(m_TextString, m_Color);
		m_pText->Update();
		m_pTexture2D = m_pText->GetTextTexture();
		FillTextureData();
	}

	void TextComponent::SetColor(const SDL_Color& color)
	{
		m_Color = color;
		if ( m_pText )
		{
			m_pText->SetColor(m_Color);
		}
		else
		{
			m_pText = new Text(m_TextString, ResourceManager::GetInstance().LoadFont("Lingua.otf", 30));
			m_pText->SetTextAndColor(m_TextString, m_Color);
		}
		m_pText->Update();
		m_pTexture2D = m_pText->GetTextTexture();
	}

	void TextComponent::SetText(const std::string& text)
	{
		m_TextString = text;
		if ( m_pText )
		{
			m_pText->SetText(m_TextString);		}
		else
		{
			m_pText = new Text( m_TextString, ResourceManager::GetInstance().LoadFont("Lingua.otf", 30) );
			m_pText->SetTextAndColor(m_TextString, m_Color);
		}
		m_pText->Update();
		m_pTexture2D = m_pText->GetTextTexture();
		FillTextureData();
	}

	void TextComponent::FillTextureData()
	{
		auto transform = m_pParent->GetComponent<TransformComponent>();
		SDL_QueryTexture(m_pTexture2D->GetSDLTexture(), NULL, NULL, &m_TextureInfo.textureRect.w, &m_TextureInfo.textureRect.h);
		m_TextureInfo.sourceRectange.w = m_TextureInfo.textureRect.w;
		m_TextureInfo.sourceRectange.h = m_TextureInfo.textureRect.h;
		m_TextureInfo.sourceRectange.x = 0;
		m_TextureInfo.sourceRectange.y = 0;

		//default info
		m_TextureInfo.destinationRectangle.x = int(transform->GetPosition().x);
		m_TextureInfo.destinationRectangle.y = int(transform->GetPosition().y);
		m_TextureInfo.destinationRectangle.w = int(m_TextureInfo.sourceRectange.w * transform->GetScale().x);
		m_TextureInfo.destinationRectangle.h = int(m_TextureInfo.sourceRectange.h * transform->GetScale().y);
	}

}