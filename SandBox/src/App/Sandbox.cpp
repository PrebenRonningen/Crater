#include "SandBoxPCH.h"
#include "SandBox.h"

#include "Scenes/SandBoxScene.h"

void Sandbox::LoadGame() const
{
	//InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::ButtonA, ButtonState::ButtonDown), new PressedTestCommand);
	//InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::ButtonX, ButtonState::ButtonUp), new ReleasedTestCommand);
	//InputManager::GetInstance().AssignCommand(std::tuple(0, ControllerButton::DPadRigh, ButtonState::ButtonRepeat), new RepeatingTestCommand);
	using namespace CraterEngine;
	auto& scene = SceneManager::GetInstance().CreateScene<SandBoxScene>("SandBoxScene");
	scene.Initialize();

}


