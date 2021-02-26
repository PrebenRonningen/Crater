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
		CraterEngine::InputManager::GetInstance().AssignCommand(std::tuple(0, CraterEngine::ControllerButton::ButtonA, CraterEngine::ButtonState::ButtonDown), new CraterEngine::PressedTestCommand);
		CraterEngine::InputManager::GetInstance().AssignCommand(std::tuple(0, CraterEngine::ControllerButton::ButtonX, CraterEngine::ButtonState::ButtonUp), new CraterEngine::ReleasedTestCommand);
		CraterEngine::InputManager::GetInstance().AssignCommand(std::tuple(0, CraterEngine::ControllerButton::DPadRigh, CraterEngine::ButtonState::ButtonRepeat), new CraterEngine::RepeatingTestCommand);
	}

	~Sandbox()
	{

	}
};


int main(int , char* [])
{
	Sandbox* eng = new Sandbox();
	
	eng->Run();

	delete eng;
	eng = nullptr;

	return 0;
}