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
#include "Scenes/DefaultScene.h"
#include "Services/ServiceLocator.h"
#include "Services/Sound/SimpleSDL2AudioMaster.h"
#include "Services/Sound/LoggingSoundSystem.h"


using namespace std;
using namespace std::chrono;

namespace CraterEngine
{
	void Crater::Initialize()
	{
		if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0 )
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
		auto& scene = SceneManager::GetInstance().CreateScene<DefaultScene>("DefaultScene");
		scene.Initialize();
	}

	void Crater::Cleanup()
	{
		//ImGui_ImplOpenGL2_Shutdown();
		//ImGui_ImplSDL2_Shutdown();
		//ImGui::DestroyContext();
		ServiceLocator::Destroy();
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

		ServiceLocator::RegisterSoundSystem(new LoggingSoundSystem(new SimpleSDL2AudioMaster()));

		auto& soundService = ServiceLocator::GetSoundService();
		soundService;
		//
		//soundService.AddAudio("../Crater/3rdParty/Simple-SDL2-Audio-master/sounds/door2.wav");
		//size_t soundId = soundService.AddAudio( "../Crater/3rdParty/Simple-SDL2-Audio-master/sounds/door1.wav" );
		//soundService.PlaySound(soundId, SDL_MIX_MAXVOLUME / 4);
		//soundService.PlayMusic("../Crater/3rdParty/Simple-SDL2-Audio-master/music/road.wav", SDL_MIX_MAXVOLUME / 10);

		LoadGame();

		#pragma region ImGuiSetup
		//IMGUI_CHECKVERSION();
		//ImGui::CreateContext();
		//ImGuiIO& io = ImGui::GetIO(); (void) io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		////io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		////io.ConfigViewportsNoAutoMerge = true;
		////io.ConfigViewportsNoTaskBarIcon = true;

		//// Setup Dear ImGui style
		//ImGui::StyleColorsDark();
		////ImGui::StyleColorsClassic();

		//// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		//ImGuiStyle& style = ImGui::GetStyle();
		//if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
		//{
		//	style.WindowRounding = 0.0f;
		//	style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		//}

		//ImGui_ImplSDL2_InitForOpenGL(m_Window, SDL_GL_GetCurrentContext());
		//ImGui_ImplOpenGL2_Init();
		///*
		//bool openWindow = true;
		//int windowFlags = 0;
		//windowFlags |= ImGuiWindowFlags_NoResize;
		//windowFlags |= ImGuiWindowFlags_NoCollapse;

		//static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
		//ImGuiTreeNodeFlags node_flags = base_flags;
		//static int selection_mask = 1;
		//int node_clicked = -1;
		//std::string nodeText[]{ "Single Player", "Co-Op", "Versus" };

		//*/
		#pragma endregion

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

				#pragma region ImguiRender
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
				//renderer.Present();

				//if ( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable )
				//{
				//	SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
				//	SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
				//	ImGui::UpdatePlatformWindows();
				//	ImGui::RenderPlatformWindowsDefault();
				//	SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
				//}
				#pragma endregion
			}
		}
		Cleanup();
	}
}