#pragma once
#include "Crater/Managers/Singleton.h"

struct SDL_Window;
struct SDL_Renderer;

namespace CraterEngine
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Present() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		//void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect&  dest, const SDL_Rect& src) const;

		SDL_Renderer* GetSDLRenderer() const
		{
			return m_Renderer;
		}
	private:
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_pWindow;
	};
}