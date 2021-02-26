#include "CraterPCH.h"
#include "Crater.h"
#include <chrono>
#include <thread>
#include "Crater/Components/Components.h"
#include "Crater/Managers/InputManager.h"
#include "Crater/Managers/SceneManager.h"
#include "Renderer.h"
#include "Crater/Managers/ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"

using namespace std;
using namespace std::chrono;

namespace CraterEngine
{
	void Crater::Initialize()
	{
		if ( SDL_Init(SDL_INIT_VIDEO) != 0 )
		{
			throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
		}

		m_Window = SDL_CreateWindow(
			"Programming 4 assignment",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			640,
			480,
			SDL_WINDOW_OPENGL
		);
		if ( m_Window == nullptr )
		{
			throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
		}

		Renderer::GetInstance().Init(m_Window);
	}
	

	/**
	 * Code constructing the scene world starts here
	 */
	void Crater::LoadGame() const
	{
		auto& scene = SceneManager::GetInstance().CreateScene("Demo");
		
		{
			//Background
			GameObject* go = new GameObject();
			go->AddComponent<TransformComponent>();
			go->AddComponent<RenderableComponent>();
			RenderableComponent* rendererComp = go->GetComponent<RenderableComponent>();
			rendererComp->SetTexture("background.jpg");
			scene.Add(go);
		}
		{	// Text
			GameObject* go = new GameObject();
			go->AddComponent<TransformComponent>();
			TransformComponent* transformComp = go->GetComponent<TransformComponent>();
			go->AddComponent<RenderableComponent>();		
			RenderableComponent* renderComp = go->GetComponent<RenderableComponent>();
			renderComp->SetTextAndColor("Programming 4 Assignment");
			auto texInfo = renderComp->GetTexInfo().textureRect;
			transformComp->SetPosition(320 - texInfo.w / 2.f, 150, 0);
			scene.Add(go);
		}
		{ // Logo
			GameObject* go = new GameObject();
			go->AddComponent<TransformComponent>();
			go->AddComponent<RenderableComponent>();

			RenderableComponent* renderComp = go->GetComponent<RenderableComponent>();
			renderComp->SetTexture("logo.png");
			auto texInfo = renderComp->GetTexInfo().textureRect;

			TransformComponent* transformComp = go->GetComponent<TransformComponent>();
			transformComp->SetPosition(320 - texInfo.w/2.f, 220 - texInfo.h /2.f, 0);
			scene.Add(go);
		}
		{	// FPS
			GameObject* go = new GameObject();
			go->AddComponent<TransformComponent>();
			TransformComponent* transformComp = go->GetComponent<TransformComponent>();
			transformComp->SetPosition(20, 20, 0);
			go->AddComponent<RenderableComponent>();
			go->AddComponent<FPSComponent>();
			scene.Add(go);
		}

		scene.Initialize();
	}

	void Crater::Cleanup()
	{
		Renderer::GetInstance().Destroy();
		SceneManager::GetInstance().Destroy();
		InputManager::GetInstance().Destroy();
		SDL_DestroyWindow(m_Window);
		m_Window = nullptr;
		SDL_Quit();
	}

	void Crater::Run()
	{
		Initialize();

		// tell the resource manager where he can find the game data
		ResourceManager::GetInstance().Init("../Crater/Data/");

		LoadGame();

		{
			auto& renderer = Renderer::GetInstance();
			auto& sceneManager = SceneManager::GetInstance();
			auto& input = InputManager::GetInstance();

			auto previousTime = high_resolution_clock::now();
			bool doContinue = true;
			while ( doContinue )
			{
				const auto currentTime = high_resolution_clock::now();
				float deltaTime = std::chrono::duration<float>(currentTime - previousTime).count();
				auto pretime = currentTime - previousTime;
				previousTime = currentTime;

				doContinue = input.ProcessInput();
				
				sceneManager.Update(deltaTime);
				renderer.Render();
			}
		}

		Cleanup();
	}
}