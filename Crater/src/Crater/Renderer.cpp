#include "CraterPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "Crater/Managers/SceneManager.h"
#include "Crater/Objects/Texture2D.h"

namespace CraterEngine
{
	int GetOpenGLDriverIndex()
	{
		auto openglIndex = -1;
		const auto driverCount = SDL_GetNumRenderDrivers();
		for ( auto i = 0; i < driverCount; i++ )
		{
			SDL_RendererInfo info;
			if ( !SDL_GetRenderDriverInfo(i, &info) )
				if ( !strcmp(info.name, "opengl") )
					openglIndex = i;
		}
		return openglIndex;
	}

	void Renderer::Init(SDL_Window* window)
	{
		m_pWindow = window;
		m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if ( m_Renderer == nullptr )
		{
			throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
		}
	}

	void Renderer::Render() const
	{
		SDL_RenderClear(m_Renderer);

		//ImGui_ImplOpenGL2_NewFrame();
		//ImGui_ImplSDL2_NewFrame(m_pWindow);
		//ImGui::NewFrame();

		SceneManager::GetInstance().Render();

		SDL_RenderPresent(m_Renderer);

	}

	void Renderer::Present() const
	{
		// Rendering
	//	ImGui::Render();
	//	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

		SDL_RenderPresent(m_Renderer);
	}

	void Renderer::Destroy()
	{
		if ( m_Renderer != nullptr )
		{
			SDL_DestroyRenderer(m_Renderer);
			m_Renderer = nullptr;
		}
	}

	void Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
	{
		SDL_Rect dst;
		dst.x = static_cast<int>( x );
		dst.y = static_cast<int>( y );
		SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
	}

	void Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect& dest, const SDL_Rect& src) const
	{
		SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dest);
	}
}