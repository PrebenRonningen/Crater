#include "CraterPCH.h"
#include "Crater.h"
#include <chrono>
#include <thread>
#include "Crater/Components/CoreComponents.h"
#include "Crater/Managers/InputManager.h"
#include "Crater/Managers/SceneManager.h"
#include "Crater/Managers/ResourceManager.h"
#include "Renderer.h"
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
			transformComp->SetPosition(320 - texInfo.w / 2.f, 220 - texInfo.h / 2.f, 0);
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
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

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


		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void) io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplSDL2_InitForOpenGL(m_Window, SDL_GL_GetCurrentContext());
		ImGui_ImplOpenGL2_Init();
		/*
		bool openWindow = true;
		int windowFlags = 0;
		windowFlags |= ImGuiWindowFlags_NoResize;
		windowFlags |= ImGuiWindowFlags_NoCollapse;

		static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
		ImGuiTreeNodeFlags node_flags = base_flags;
		static int selection_mask = 1;
		int node_clicked = -1;
		std::string nodeText[]{ "Single Player", "Co-Op", "Versus" };

		*/

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
				/*
				{
					ImGui::Begin("Select Gamemode", &openWindow, windowFlags);

					for ( int i = 0; i < 3; i++ )
					{
						node_flags = base_flags;
						const bool is_selected = ( selection_mask & ( 1 << i ) ) != 0;
						if ( is_selected )
							node_flags |= ImGuiTreeNodeFlags_Selected;

						node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
						ImGui::TreeNodeEx((void*) (intptr_t) i, node_flags, nodeText[i].c_str());
						if ( ImGui::IsItemClicked() )
							node_clicked = i;
					}
					if ( node_clicked != -1 )
					{
						selection_mask = ( 1 << node_clicked );
					}
					ImGui::End();
				}
				*/
				renderer.Present();

				if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
				{
					SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
					SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
					ImGui::UpdatePlatformWindows();
					ImGui::RenderPlatformWindowsDefault();
					SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
				}
			}
		}
		Cleanup();
	}
}