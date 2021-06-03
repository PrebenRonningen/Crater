#pragma once
#include "Crater/Components/Component.h"
#include <string>
#include "Texture2D.h"
namespace CraterEngine
{
	class Font;
	class Text final 
	{
	public:
		Text(const std::string& text, Font* pFont, const SDL_Color& color = SDL_Color{ 255, 255, 255 });
		~Text();

	#pragma region delete
		Text(const Text& other) = delete;
		Text(Text&& other) = delete;
		Text& operator=(const Text& other) = delete;
		Text& operator=(Text&& other) = delete;
	#pragma endregion

		void Update(const float dt = 0);

		void SetTextAndColor(const std::string& text, const SDL_Color& color = { 255, 255, 255 });
		void SetColor(const SDL_Color& color = { 255, 255, 255 });
		void SetText(const std::string& text);
		std::string GetText() const { return m_PrimaryText; };
		Texture2D* GetTextTexture();
	private:
		Texture2D* m_pTexture;
		Font* m_pFont;
		std::string m_Text;
		std::string m_PrimaryText;
		SDL_Color m_Color;
		bool m_NeedsUpdate;
	};
}
