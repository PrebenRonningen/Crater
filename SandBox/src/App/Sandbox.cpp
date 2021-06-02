#include "SandBoxPCH.h"
#include <CraterEngine.h>

#include "Observers/HealthObserver.h"
#include "Observers/ScoreObserver.h"
#include "Components/PlayerComponent.h"
#include "Commands/ScoreCommand.h"
#include "Commands/LoseLifeCommand.h"
#include "Components/HealthDisplayComponent.h"
#include "Components/ScoreDisplayComponent.h"

#include "Scenes/SandBoxScene.h"


#include "src/audio.h"
#include "src/audio.c"
//


class Sandbox : public CraterEngine::Crater
{
public:
	Sandbox()
	{

	}

	virtual void LoadGame() const
	{
		//InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::ButtonA, ButtonState::ButtonDown), new PressedTestCommand);
		//InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::ButtonX, ButtonState::ButtonUp), new ReleasedTestCommand);
		//InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::DPadRigh, ButtonState::ButtonRepeat), new RepeatingTestCommand);
		using namespace CraterEngine;
		auto& scene = SceneManager::GetInstance().CreateScene<SandBoxScene>("SandBoxScene");
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

