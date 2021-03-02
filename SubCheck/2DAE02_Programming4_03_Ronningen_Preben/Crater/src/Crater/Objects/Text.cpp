#include "CraterPCH.h"
#include <SDL_ttf.h>

#include "Text.h"
#include "Crater/Renderer.h"
#include "Font.h"
#include "Texture2D.h"

namespace CraterEngine
{
	Text::Text(const std::string& text, Font* pFont, const SDL_Color& color)
		: m_NeedsUpdate(true)
		, m_Text(text)
		, m_pFont(pFont)
		, m_pTexture(nullptr)
		, m_Color{color}
	{
	}


	Text::~Text()
	{
		if ( m_pFont )
		{
			delete m_pFont;
			m_pFont = nullptr;
		}
	}

	void Text::Update(const float)
	{
		if ( m_NeedsUpdate )
		{
			SDL_Surface* const surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
			if ( surf == nullptr )
			{
				throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			}
			SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
			if ( texture == nullptr )
			{
				throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
			}
			SDL_FreeSurface(surf);
			if ( m_pTexture != nullptr )
			{
				delete m_pTexture;
				m_pTexture = nullptr;
			}
			m_pTexture = new Texture2D(texture);
			m_NeedsUpdate = false;
		}
	}

	// This implementation uses the "dirty flag" pattern
	void Text::SetTextAndColor(const std::string& text, const SDL_Color& color)
	{
		if(m_PrimaryText.empty()) m_PrimaryText = text;
		m_Text = text;
		m_Color = color;
		m_NeedsUpdate = true;
	}
	void Text::SetColor(const SDL_Color& color)
	{
		m_Color = color;
		m_NeedsUpdate = true;
	}
	void Text::SetText(const std::string& text)
	{
		m_Text = text;
		m_NeedsUpdate = true;
	}

	Texture2D* Text::GetTextTexture()
	{
		return m_pTexture;
	}

}