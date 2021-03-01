#include <CraterPCH.h>
#include <CraterEngine.h>

class Sandbox : public CraterEngine::Crater
{
public:
	Sandbox()
	{

	}

	virtual void LoadGame() const
	{
		using namespace CraterEngine;
		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::ButtonA, ButtonState::ButtonDown), new PressedTestCommand);
		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::ButtonX, ButtonState::ButtonUp), new ReleasedTestCommand);
		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::ButtonX, ButtonState::ButtonUp), new ReleasedTestCommand);
		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::ButtonX, ButtonState::ButtonUp), new PressedTestCommand);
		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::ButtonX, ButtonState::ButtonUp), new ReleasedTestCommand);
		InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::DPadRigh,ButtonState::ButtonRepeat), new RepeatingTestCommand);

		Scene& scene = SceneManager::GetInstance().CreateScene("Sandbox Demo");
		
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

	~Sandbox()
	{
		
	}
};


int main(int , char* [])
{
	Sandbox* eng = new Sandbox();
	
	eng->Run();
	if ( eng )
	{
		delete eng;
		eng = nullptr;
	}

	return 0;
}