#include "CraterPCH.h"
#include "TextComponent.h"
#include "Crater/Managers/ResourceManager.h"
#include "RenderableComponent.h"
namespace CraterEngine
{
	TextComponent::TextComponent(const GameObject* parent, const std::string& text, const SDL_Color& color)
		:Component(parent)
		, m_pTexture2D{nullptr}
		, m_TextString{text}
		, m_pText{nullptr}
		, m_pParentRenderComponent{nullptr}
		, m_Color{ color }
	{		
		if ( !parent->HasComponent<RenderableComponent>() )
		{
			std::cout << "[Warning] ParentObject needs RenderComponent\n";
		}
		else
		{
			m_pParentRenderComponent = parent->GetComponent<RenderableComponent>();
			if(!m_TextString.empty() )
				SetTextAndColor(m_TextString, m_Color);
		}
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
			m_pText->SetTextAndColor(m_TextString, m_Color);
			m_pText->Update();
			m_pTexture2D = m_pText->GetTextTexture();
			PassTextureToRenderComponent();
			return;
		}
		m_pText->SetTextAndColor(m_TextString, m_Color);
		m_pText->Update();
		m_pTexture2D = m_pText->GetTextTexture();
		PassTextureToRenderComponent();
	}

	void TextComponent::SetColor(const SDL_Color& color)
	{
		m_Color = color;
		if ( m_pText )
		{
			m_pText->SetColor(m_Color);
			m_pText->Update();
		}
		else
		{
			m_pText = new Text(m_TextString, ResourceManager::GetInstance().LoadFont("Lingua.otf", 30));
			m_pText->SetTextAndColor(m_TextString, m_Color);
			m_pText->Update();
			m_pTexture2D = m_pText->GetTextTexture();
		}
		PassTextureToRenderComponent();
	}

	void TextComponent::SetText(const std::string& text)
	{
		m_TextString = text;
		if ( m_pText )
		{
			m_pText->SetText(m_TextString);
			m_pText->Update();
			m_pTexture2D = m_pText->GetTextTexture();
		}
		else
		{
			m_pText = new Text( m_TextString, ResourceManager::GetInstance().LoadFont("Lingua.otf", 30) );
			m_pText->SetTextAndColor(m_TextString, m_Color);
			m_pText->Update();
			m_pTexture2D = m_pText->GetTextTexture();
		}
		PassTextureToRenderComponent();
	}

	bool TextComponent::Initialize()
	{
		if(m_IsInitialized) return true;
		if ( !m_pTexture2D )
			SetTextAndColor(m_TextString, m_Color);
		m_IsInitialized = true;
		return true;
	}

	void TextComponent::PassTextureToRenderComponent()
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